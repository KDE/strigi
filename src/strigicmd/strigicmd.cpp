/* This file is part of Strigi Desktop Search
 *
 * Copyright (C) 2007 Jos van den Oever <jos@vandenoever.info>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */
#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <string>
#include <algorithm>
#include "combinedindexmanager.h"
#include "analyzerconfiguration.h"
#include "indexer.h"
#include "strigiconfig.h"
using namespace std;
using namespace Strigi;

/*
 * Help function for printing to stderr: fprintf(stderr, 
 */
int
pe(const char *format, ...) {
    va_list arg;
    int done;
    va_start(arg, format);
    done = vfprintf(stderr, format, arg);
    va_end(arg);
    return done;
}
/**
 * This is the main for implementing a command line program that can create
 * and query indexes.
 **/
int
usage(int argc, char** argv) {
    pe("%s: program for creating and querying indices\n", argv[0]);
    return 1; 
}
int
create(int argc, char** argv) {
    // parse arguments
    string backend;
    string indexdir;
    vector<string> dirs;
    int i = 1;
    while (++i < argc) {
        const char* arg = argv[i];
        if (!strcmp("-t", arg)) {
            if (++i == argc) {
                return usage(argc, argv);
            }
            backend.assign(argv[i]);
        } else if (!strcmp("-d", arg)) {
            if (++i == argc || indexdir.length()) {
                return usage(argc, argv);
            }
            indexdir.assign(argv[i]);
        } else {
            dirs.push_back(argv[i]);
        }
    }

    // check arguments: backend
    const vector<string>& backends = CombinedIndexManager::backEnds();
    // if there is only one backend, the backend does not have to be specified
    if (backend.size() == 0) {
        if (backends.size() == 1) {
            backend = backends[0];
        } else {
            pe("Specify a backend.\n");
            return usage(argc, argv);
        }
    }
    vector<string>::const_iterator b
        = find(backends.begin(), backends.end(), backend);
    if (b == backends.end()) {
        pe("Invalid index type. Choose one from ");
        for (uint j=0; j<backends.size()-1; ++j) {
            pe("%s, ", backends[j].c_str());
        }
        pe("%s\n", backends[backends.size()-1].c_str());
        return 1;
    }
    // check arguments: indexdir
    if (indexdir.length() == 0) {
        pe("Provide a dir to write the index to with -d.\n");
        return usage(argc, argv);
    }
    // check arguments: dirs
    if (dirs.size() == 0) {
        pe("'%s' '%s'\n", backend.c_str(), indexdir.c_str());
        pe("Provide directories to index.\n");
        return usage(argc, argv);
    }

    AnalyzerConfiguration config;
    Indexer indexer(indexdir, backend, config);
    vector<string>::const_iterator j;
    for (j = dirs.begin(); j != dirs.end(); ++j) {
        indexer.index(j->c_str());
    }

    return 0;
}
int
main(int argc, char** argv) {
    if (argc < 2) { 
        return usage(argc, argv);
    }
    const char* cmd = argv[1];
    if (!strcmp(cmd,"create")) {
        return create(argc, argv);
    } else {
        return usage(argc, argv);
    }
    return 0;
}