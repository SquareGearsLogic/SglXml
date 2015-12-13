/*
Licensed to the Square Gears Logic (SGL) under one
or more contributor license agreements.  See the NOTICE file
distributed with this work for additional information
regarding copyright ownership.  The SGL licenses this file
to you under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance
with the License.  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing,
software distributed under the License is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied.  See the License for the
specific language governing permissions and limitations
under the License.
*/

#include <fstream>

#include "../SglStringUtils/SglStringUtils.h"
#include "SglXml.h"

namespace SglXml
{
using namespace SglUtils;

SglXmlElementPtr SglXml::parseFile(string filename)
{
    SglXmlElementPtr dom;
    bool result = true;
    ifstream infile(filename.c_str());
    try{
        string line;
        SglXmlElementPtr currentParent;
        while (getline(infile, line))
        {
            SglStringUtils::trim(line);
            if (line.find("--") != string::npos)
                continue;

            int tagBegin = line.find("<");
            if (tagBegin == string::npos)
                continue;

            int tagEnd = line.find(">");
            if (tagEnd == string::npos)
                continue;

            int tagEob = line.find("/");
            if (tagEob == string::npos)
            {
                string SglXmlElementStr = line.substr(tagBegin+1, tagEnd-1);

                if (currentParent != NULL)
                {
                    SglXmlElementPtr newBlock(new SglXmlElement(currentParent, SglXmlElementStr));
                    currentParent->addChild(newBlock);
                    currentParent.reset();
                    currentParent = newBlock;
                }
                else
                {
                    SglXmlElementPtr nullPtr;
                    SglXmlElementPtr newParent(new SglXmlElement(nullPtr, SglXmlElementStr));
                    currentParent.reset();
                    currentParent = newParent;
                }

                continue;
            }
            else if(tagEob == tagBegin+1)
            {

                if (currentParent->getParent() == NULL)
                {
                    dom = currentParent;
                    break;
                }
                currentParent = currentParent->getParent();
                continue;
            }
            else
            {
                string elementStr = line.substr(tagBegin+1, tagEnd-2);
                SglXmlElementPtr newElmnt(new SglXmlElement(currentParent, elementStr));
                currentParent->addChild(newElmnt);
                continue;
            }
        }
    }catch(...){
        result = false;
    }
    infile.close();

    return SglXmlElementPtr(dom);
}

void SglXml::saveFile(SglXmlElementPtr dom, string filename, bool override)
{
    ofstream myfile;
    myfile.open (filename.c_str(), (override ? ios::trunc : ios::app ));
    myfile << dom->toString();
    myfile.close();
}

}
