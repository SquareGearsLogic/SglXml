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

#ifndef SGLXML_H
#define SGLXML_H

#include <string>

#include "SglXmlElement.h"

namespace SglXml
{
using namespace std;

/**
 * @brief Lightweight implementation of XML-Like Processor.
 * it doesn't use all features of XML Standard but
 * supports some major things, like
 * - one element per line;
 * - single root element;
 * - elements with <start> and </stop> tags;
 * - as well as <empty-tags/>;
 * - attributes of elements;
 * - and -- line comments (<!-- regular XML comments are not supported -->).
 */
class SglXml
{
public:
    /**
     * @brief creates a DOM structure based on xml-like file.
     *
     */
    static SglXmlElementPtr parseFile(string filename);
    static void saveFile(SglXmlElementPtr dom, string filename, bool override=true);


protected:
    SglXml(string filename);
};

};
#endif // SGLXML_H
