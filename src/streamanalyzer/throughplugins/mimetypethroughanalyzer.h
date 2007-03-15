/* This file is part of Strigi Desktop Search
 *
 * Copyright (C) 2006 Jos van den Oever <jos@vandenoever.info>
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
#ifndef MIMETYPETHROUGHANALYZER_H
#define MIMETYPETHROUGHANALYZER_H

#include "streamthroughanalyzer.h"
#include "analyzerplugin.h"
extern "C" {
    #include <magic.h>
}
class STRIGI_PLUGIN_API MimeTypeThroughAnalyzer
        : public Strigi::StreamThroughAnalyzer {
private:
    magic_t magic;
    Strigi::AnalysisResult* idx;
public:
    MimeTypeThroughAnalyzer();
    ~MimeTypeThroughAnalyzer();
    void setIndexable(Strigi::AnalysisResult* i) { idx = i; }
    jstreams::InputStream *connectInputStream(jstreams::InputStream *in);
    bool isReadyWithStream();
};

#endif