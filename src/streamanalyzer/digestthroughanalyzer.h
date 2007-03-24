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
#ifndef DIGESTTHROUGHANALYZER_H
#define DIGESTTHROUGHANALYZER_H

#include "streamthroughanalyzer.h"
#include "cnstr.h"

namespace jstreams {
    class DigestInputStream;
}
namespace Strigi {
    class RegisteredField;
    class FieldRegister;
}

class DigestThroughAnalyzer : public Strigi::StreamThroughAnalyzer {
private:
    static std::string shafieldname;
    jstreams::DigestInputStream *stream;
    Strigi::AnalysisResult* indexable;
    const Strigi::RegisteredField* shafield;
public:
    DigestThroughAnalyzer(Strigi::FieldRegister& reg);
    ~DigestThroughAnalyzer();
    void setIndexable(Strigi::AnalysisResult*);
    jstreams::InputStream *connectInputStream(jstreams::InputStream *in);
    bool isReadyWithStream();
};

class DigestThroughAnalyzerFactory
        : public Strigi::StreamThroughAnalyzerFactory {
private:
    const char* getName() const {
        return "DigestThroughAnalyzer";
    }
    Strigi::StreamThroughAnalyzer* newInstance(Strigi::FieldRegister& reg)
            const {
        return new DigestThroughAnalyzer(reg);
    }
};

#endif
