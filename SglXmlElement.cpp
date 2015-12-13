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

#include "..\SglStringUtils\SglStringUtils.h"
#include "SglXml.h"
#include "SglXmlElement.h"

namespace SglXml
{
using namespace SglUtils;

typedef pair<std::string, std::string> StrStrPair;

SglXmlElement::SglXmlElement(SglXmlElementPtr parent, string &xmlLine) :
    mParent(parent),
    mTag("")
{
    parseLine(xmlLine);
}

SglXmlElement::~SglXmlElement()
{
    mChilds.clear();
}

SglXmlElementPtr SglXmlElement::getParent()
{
    return mParent;
}

void SglXmlElement::addChild(SglXmlElementPtr child)
{
    mChilds.push_back(child);
}

void SglXmlElement::parseLine(string& xmlLine)
{
    string work = xmlLine;
    SglStringUtils::trim(work);
    int pos = work.find(" ");
    if (pos == string::npos)
    {
        mTag = xmlLine;
        return;
    }
    mTag = work.substr(0, pos);
    work = work.substr(pos, xmlLine.length() - pos);
    readPropValues(work);
}

void SglXmlElement::readPropValues(const string& elementStr)
{
    // NOTE: I could make it with one iterator, but in this form it's more readable and debuggable.
    int token = 0;
    while (token < elementStr.length())
    {
        int pos1 = elementStr.find("=", token);
        if (pos1 == string::npos)
            return;
        string key = elementStr.substr(token, pos1 - token);
        key = SglStringUtils::trim(key);
        pos1 ++;

        int pos2 = elementStr.find('"', pos1);
        if (pos2 == string::npos)
            return;
        pos2++;

        int pos3 = elementStr.find('"', pos2);
        if (pos3 == string::npos)
            return;
        string value = elementStr.substr(pos2, pos3-pos2);
        pos3++;

        mAttributes.insert(StrStrPair(key, value));
        token = pos3;
    }
}

vector<SglXmlElementPtr> SglXmlElement::getChilds()
{
    return mChilds;
}

string SglXmlElement::getTag()
{
    return mTag;
}

string SglXmlElement::getAttribute(string attribute)
{
    if (mAttributes.find(attribute) != mAttributes.end())
        return mAttributes.find(attribute)->second;
    return "";
}

vector<string> SglXmlElement::getAttributes()
{
    vector<string> result;
    for(map<string, string>::iterator it = mAttributes.begin(); it != mAttributes.end(); ++it)
      result.push_back(it->first);
    return result;
}

string SglXmlElement::toString(bool isPrintCilds, bool isBeautify, int spacesInTab, int tabs)
{
    string result = string (spacesInTab*tabs, ' ') + "<" + mTag;
    for(map<string, string>::iterator it = mAttributes.begin(); it != mAttributes.end(); it++)
        result += string(" ") + (*it).first + "=\"" + (*it).second + "\"";
    if (isPrintCilds && mChilds.size() != 0)
    {
        result += string(">") + (isBeautify ? "\n" : "");
        for (SglXmlElementPtr child : mChilds)
            result += child->toString(isPrintCilds, isBeautify, spacesInTab, tabs+1);
        result += (isBeautify ? string (spacesInTab*tabs, ' ') : "") + "</" + mTag +">" + (isBeautify ? "\n" : "");
    }
    else
    {
        result += string("/>") + (isBeautify ? "\n" : "");
    }
    return result;
}

}
