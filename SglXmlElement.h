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

#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <string>
#include <vector>
#include <tr1/memory>
#include <map>

namespace SglXml
{
using namespace std;

class SglXmlElement;

typedef tr1::shared_ptr<SglXmlElement> SglXmlElementPtr;

/**
 * @brief Represents the Xml Element that may or may not contain
 * other XmlElements and attributes.
 */
class SglXmlElement
{
public:
    SglXmlElement(SglXmlElementPtr parent, string& xmlLine);
    ~SglXmlElement();
    SglXmlElementPtr getParent();
    void addChild(SglXmlElementPtr child);
    void parseLine(string& xmlLine);
    vector<SglXmlElementPtr> getChilds();
    string getTag();
    string getAttribute(string attribute);
    vector<string> getAttributes();
    string toString(bool isPrintCilds=false, bool isBeautify=false, int spacesInTab=4, int tabs=0);

protected:
    SglXmlElement();
    void readPropValues(const string& elementStr);

protected:
    SglXmlElementPtr mParent;
    vector<string> mProps;
    vector<SglXmlElementPtr> mChilds;
    map<string, string> mAttributes;
    string mTag;
};

};
#endif // XMLPARSER_H
