#include "gzipinputstream.h"
#include <zlib.h>
using namespace jstreams;

GZipInputStream::GZipInputStream(StreamBase<char>* input, ZipFormat format) {
    // initialize values that signal state
    status = Ok;
    zstream = 0;
    finishedInflating = false;

    this->input = input;

    // TODO: check first bytes of stream before allocating buffer
    // 0x42 0x5a 0x68 0x39 0x31
    if (format != GZIPFORMAT && !checkMagic()) {
        error = "Magic bytes are wrong.";
        status = Error;
        return;
    }

    // initialize the buffer
    buffer.setSize(262144);

    // initialize the z_stream
    zstream = (z_stream_s*)malloc(sizeof(z_stream_s));
    zstream->zalloc = Z_NULL;
    zstream->zfree = Z_NULL;
    zstream->opaque = Z_NULL;
    zstream->avail_in = 0;
    zstream->next_in = Z_NULL;
    // initialize for reading gzip streams
    // for reading libz streams, you need inflateInit(zstream)
    int r;
    switch(format) {
    case ZLIBFORMAT:
        r = inflateInit(zstream);
        break;
    case GZIPFORMAT:
        r = inflateInit2(zstream, 15+16);
        break;
    case ZIPFORMAT:
    default:
        r = inflateInit2(zstream, -MAX_WBITS);
        break;
    }
    if (r != Z_OK) {
        error = "Error initializing GZipInputStream.";
        dealloc();
        status = Error;
        return;
    }
    // signal that we need to read into the buffer
    zstream->avail_out = 1;
}
GZipInputStream::~GZipInputStream() {
    dealloc();
}
void
GZipInputStream::dealloc() {
    if (zstream) {
        inflateEnd(zstream);
        free(zstream);
        zstream = 0;
    }
}
bool
GZipInputStream::checkMagic() {
    unsigned char buf[2];
    input->mark(2);
    const char *ptr;
    int32_t nread;
    int32_t total = 0;
    do {
        nread = input->read(ptr, 2-total);
        if (nread == -1) {
            error = input->getError();
            return false;
        }
        for (int32_t i=0; i<nread; i++) {
            buf[i+total] = ptr[i];
        }
        total += nread;
    } while (total < 2);
    input->reset();
    return buf[0] == 0x1f && buf[1] == 0x8b;
}
/**
 * Obtain small performance gain by reusing the object and its
 * allocated buffer and zstream.
 **/
void
GZipInputStream::restart(StreamBase<char>* input) {
    if (zstream == 0) {
        error = "Cannot restart GZipInputStream: state invalid.";
        status = Error;
        return;
    }
    this->input = input;
    int r = inflateReset(zstream);
    if (r != Z_OK) {
        status = Error;
        return;
    }
    status = Ok;
    finishedInflating = false;
    // signal that we need to read into the buffer
    zstream->avail_out = 1;
}
/*int32_t
GZipInputStream::read(const char*& start, int32_t ntoread) {
    // if an error occured earlier, signal this
    if (status) return status;

    // if we cannot read and there's nothing in the buffer
    // (this can maybe be fixed by calling reset)
    if (finishedInflating && buffer.avail == 0) return Eof;

    // check if there is still data in the buffer
    if (buffer.avail == 0) {
        decompressFromStream();
        if (status) return status;
    }

    // set the pointers to the available data
    int32_t nread = buffer.read(start, ntoread);
    return nread;
}*/
void
GZipInputStream::fillBuffer() {
    readFromStream();
}
void
GZipInputStream::readFromStream() {
    // read data from the input stream
    const char* inStart;
    int32_t nread;
    nread = input->read(inStart);
    if (nread == -1) {
        status = Error;
    }
    zstream->next_in = (Bytef*)inStart;
    zstream->avail_in = nread;
}
void
GZipInputStream::decompressFromStream() {
//    printf("decompress\n");
    // make sure there is data to decompress
    if (zstream->avail_out != 0) {
        readFromStream();
        if (status) {
            // no data was read
            return;
        }
    }
    // make sure we can write into the buffer
    int space = buffer.getWriteSpace();
    zstream->avail_out = space;
    zstream->next_out = (Bytef*)buffer.curPos;
    // decompress
    int r = inflate(zstream, Z_SYNC_FLUSH);
    // inform the buffer of the number of bytes that was read
    buffer.avail = space - zstream->avail_out;
    switch (r) {
    case Z_NEED_DICT:
        error = "Z_NEED_DICT while inflating stream.";
        status = Error;
        break;
    case Z_DATA_ERROR:
        error = "Z_DATA_ERROR while inflating stream.";
        status = Error;
        break;
    case Z_MEM_ERROR:
        error = "Z_MEM_ERROR while inflating stream.";
        status = Error;
        break;
    case Z_STREAM_END:
        // we are finished decompressing,
        // (but this stream is not yet finished)
        finishedInflating = true;
        break;
    }
}
