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

#include "analysisresult.h"
#include "deblineanalyzer.h"
#include "streamendanalyzer.h"
#include "jstreamsconfig.h"
#include "fieldtypes.h"
#include <iostream> 


using namespace Strigi;
using namespace jstreams;

const cnstr DebLineAnalyzerFactory::nameFieldName("name");
const cnstr DebLineAnalyzerFactory::versionFieldName("version");
const cnstr DebLineAnalyzerFactory::summaryFieldName("summary");
const cnstr DebLineAnalyzerFactory::maintainerFieldName("maintainer");
const cnstr DebLineAnalyzerFactory::sectionFieldName("section");
const cnstr DebLineAnalyzerFactory::dependsFieldName("depends");


void
DebLineAnalyzerFactory::registerFields(FieldRegister& r) {
    nameField = r.registerField(nameFieldName, FieldRegister::stringType,
        1, 0);
    versionField = r.registerField(versionFieldName, FieldRegister::stringType,
        1, 0);
    summaryField = r.registerField(summaryFieldName, FieldRegister::stringType,
        1, 0);
    maintainerField = r.registerField(maintainerFieldName, FieldRegister::stringType,
        1, 0);
    sectionField = r.registerField(sectionFieldName, FieldRegister::stringType,
        1, 0);
    dependsField = r.registerField(dependsFieldName, FieldRegister::stringType,
        0, 0);
}

void 
DebLineAnalyzer::startAnalysis(AnalysisResult* res)
{
    // let's assume that it is not .deb file and set isReadyWithStream() to true
    finished=6;
    if (res->fileName()!="control") return;
    res=res->parent();
    if (!res) return;
    if (res->fileName()!="control.tar.gz") return;
    res=res->parent();
    if (!res) return;
    if (strcmp(res->endAnalyzer()->getName(),"ArEndAnalyzer")) return ;

    // it is .deb file after all
    result=res;
    finished=0;
}

void 
DebLineAnalyzer::handleLine(const char* data, uint32_t length)
{
	std::string line(data,length);
	if (line.find("Package: ",0)==0) { result->setField(factory->nameField, line.substr(9,line.size())); finished++; }
	if (line.find("Description: ",0)==0) { result->setField(factory->summaryField, line.substr(13,line.size())); finished++; }
	if (line.find("Version: ")==0) { result->setField(factory->versionField, line.substr(9,line.size())); finished++; }
	if (line.find("Maintainer: ")==0) { result->setField(factory->maintainerField, line.substr(12,line.size())); finished++; }
	if (line.find("Section: ")==0) { result->setField(factory->sectionField, line.substr(9,line.size())); finished++; }
	if (line.find("Depends: ")==0) {
	    unsigned int start=9;
	    unsigned int end;
	    do {
		end=line.find(", ",start);
		if (end==std::string::npos) end=length;
		result->setField(factory->dependsField, line.substr(start, end-start));
		start=end+2;
	    } while (start<length);
	    finished++;
	}
}

bool
DebLineAnalyzer::isReadyWithStream()
{
    // analysis is finished after all 6 fields were found (name, summary, version, deps, maintainer, section)
    return finished==6; 
}

class Factory : public AnalyzerFactoryFactory {
public:
    std::list<StreamLineAnalyzerFactory*> 
    getStreamLineAnalyzerFactories() const {
        std::list<StreamLineAnalyzerFactory*> af;
        af.push_back(new DebLineAnalyzerFactory());
        return af;
    }
};

STRIGI_ANALYZER_FACTORY(Factory)