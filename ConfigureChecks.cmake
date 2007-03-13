# fixme !
IF(MINGW)
set (HAVE_SSIZE_T 1)
ENDIF(MINGW)

#need to find a few default headers:
INCLUDE(CheckIncludeFileCXX)
CHECK_INCLUDE_FILE_CXX(direct.h HAVE_DIRECT_H)          # src/streamindexer/filelister.cpp
CHECK_INCLUDE_FILE_CXX(dirent.h HAVE_DIRENT_H)          # src/streams/compat/stgdirent.cpp/.h
CHECK_INCLUDE_FILE_CXX(dlfcn.h HAVE_DLFCN_H)            # src/streamindexer/analyzerloader.cpp/.h - do we really need it in .h?
CHECK_INCLUDE_FILE_CXX(ndir.h HAVE_NDIR_H)              # src/streams/compat/stgdirent.cpp/.h
CHECK_INCLUDE_FILE_CXX(stdint.h HAVE_STDINT_H)          # src/streamindexer/indexeddocument.h - why?
CHECK_INCLUDE_FILE_CXX(socket.h HAVE_SOCKET_H)          # unused !
CHECK_INCLUDE_FILE_CXX(stddef.h HAVE_STDDEF_H)          # unused !
CHECK_INCLUDE_FILE_CXX(stdint.h HAVE_STDINT_H)          # config.h
CHECK_INCLUDE_FILE_CXX(sys/dir.h HAVE_SYS_DIR_H)        # src/streams/compat/stgdirent.cpp/.h
CHECK_INCLUDE_FILE_CXX(sys/ndir.h HAVE_SYS_NDIR_H)      # src/streams/compat/stgdirent.cpp/.h
CHECK_INCLUDE_FILE_CXX(sys/socket.h HAVE_SYS_SOCKET_H)  # unused !
CHECK_INCLUDE_FILE_CXX(sys/types.h HAVE_SYS_TYPES_H)    # unused !
CHECK_INCLUDE_FILE_CXX(unistd.h HAVE_UNISTD_H)          # src/streamindexer/pluginendanalyzer.cpp
CHECK_INCLUDE_FILE_CXX(windows.h HAVE_WINDOWS_H)        # src/streamindexer/filelister.cpp

#test for some functions that are missing on a particular system
INCLUDE(CheckFunctionExists)
CHECK_FUNCTION_EXISTS(fchdir HAVE_FCHDIR)               # unused !
CHECK_FUNCTION_EXISTS(gettimeofday HAVE_GETTIMEOFDAY)   # src/luceneindexer/cluceneindexmanager.cpp, src/luceneindexer/cluceneindexreader.cpp, src/streams/compat/timeofday.h
CHECK_FUNCTION_EXISTS(isblank HAVE_ISBLANK)             # src/streams/mailinputstream.cpp, src/streams/compat/compat.cpp
CHECK_FUNCTION_EXISTS(nanosleep HAVE_NANOSLEEP)         # src/storage/sqlitestorage.cpp, src/daemon/indexscheduler.cpp, src/searchclient/cmdlinestrigi.cpp
CHECK_FUNCTION_EXISTS(strcasecmp HAVE_STRCASECMP)       # src/streamindexer/expatsaxendanalyzer.cpp, src/streamindexer/saxendanalyzer.cpp
CHECK_FUNCTION_EXISTS(strcasestr HAVE_STRCASESTR)       # src/streams/mailinputstream.cpp
CHECK_FUNCTION_EXISTS(strlwr HAVE_STRLWR)               # src/streamindexer/ifilterendanalyzer.cpp
CHECK_FUNCTION_EXISTS(strncasecmp HAVE_STRNCASECMP)     # src/streams/mailinputstream.cpp

#test for missing types
INCLUDE(CheckTypeSize)

#test for ansi scope (needed for msvc6)
INCLUDE(TestForANSIForScope)

if(HAVE_SOCKET_H)
  set(type_check_includes ${type_check_includes} socket.h)
endif(HAVE_SOCKET_H)
if(HAVE_STDINT_H)
  set(type_check_includes ${type_check_includes} stdint.h)
endif(HAVE_STDINT_H)
if(HAVE_SYS_SOCKET_H)
  set(type_check_includes ${type_check_includes} sys/socket.h)
endif(HAVE_SYS_SOCKET_H)
if(HAVE_UNISTD_H)
  set(type_check_includes ${type_check_includes} unistd.h)
endif(HAVE_UNISTD_H)

SET(CMAKE_EXTRA_INCLUDE_FILES ${CMAKE_EXTRA_INCLUDE_FILES} ${type_check_includes})
CHECK_TYPE_SIZE(int32_t INT32_T)
CHECK_TYPE_SIZE(uint32_t UINT32_T)
CHECK_TYPE_SIZE(int64_t INT64_T)
CHECK_TYPE_SIZE(uint64_t UINT64_T)

CHECK_TYPE_SIZE("long long" SIZEOF_LONGLONG)
CHECK_TYPE_SIZE(long SIZEOF_LONG)
CHECK_TYPE_SIZE(int SIZEOF_INT)
CHECK_TYPE_SIZE(ssize_t SIZEOF_SSIZE_T)

CHECK_TYPE_SIZE(uint UINT)
CHECK_TYPE_SIZE(intptr_t INTPTR_T)
CHECK_TYPE_SIZE(socklen_t SOCKLEN_T)

INCLUDE(MacroBoolTo01)
MACRO_BOOL_TO_01(HAVE_INT32_T HAVE_INT32_T)
MACRO_BOOL_TO_01(HAVE_UINT32_T HAVE_UINT32_T)
MACRO_BOOL_TO_01(HAVE_INT64_T HAVE_INT64_T)
MACRO_BOOL_TO_01(HAVE_UINT64_T HAVE_UINT64_T)
MACRO_BOOL_TO_01(HAVE_UINT HAVE_UINT)
MACRO_BOOL_TO_01(HAVE_INTPTR_T HAVE_INTPTR_T)
MACRO_BOOL_TO_01(HAVE_SOCKLEN_T HAVE_SOCKLEN_T)

#now write out our configuration....
ADD_DEFINITIONS(-DHAVE_CONFIG_H)
CONFIGURE_FILE(
  ${strigi_SOURCE_DIR}/config.h.cmake
  ${strigi_BINARY_DIR}/config.h
)

CONFIGURE_FILE(
  ${strigi_SOURCE_DIR}/src/streams/compat/jstreamsconfig.h.cmake
  ${strigi_BINARY_DIR}/src/streams/compat/jstreamsconfig.h
)
