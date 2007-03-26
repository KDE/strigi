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
#ifndef BMPENDANALYZER
#define BMPENDANALYZER

#include "streamendanalyzer.h"

class BmpEndAnalyzerFactory;
class BmpEndAnalyzer : public Strigi::StreamEndAnalyzer {
private:
    const BmpEndAnalyzerFactory* factory;
public:
    BmpEndAnalyzer(const BmpEndAnalyzerFactory* f) :factory(f) {}
    bool checkHeader(const char* header, int32_t headersize) const;
    char analyze(Strigi::AnalysisResult& idx, jstreams::InputStream* in);
    const char* getName() const { return "BmpEndAnalyzer"; }
};

class BmpEndAnalyzerFactory : public Strigi::StreamEndAnalyzerFactory {
friend class BmpEndAnalyzer;
private:
    static const std::string typeFieldName;
    static const std::string widthFieldName;
    static const std::string heightFieldName;
    static const std::string colorDepthFieldName;
    static const std::string compressionFieldName;
    const Strigi::RegisteredField* typeField;
    const Strigi::RegisteredField* widthField;
    const Strigi::RegisteredField* heightField;
    const Strigi::RegisteredField* colorDepthField;
    const Strigi::RegisteredField* compressionField;
    const char* getName() const {
        return "BmpEndAnalyzer";
    }
    Strigi::StreamEndAnalyzer* newInstance() const {
        return new BmpEndAnalyzer(this);
    }
    void registerFields(Strigi::FieldRegister&);
};

#endif