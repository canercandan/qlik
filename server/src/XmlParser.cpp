// XmlParser.cpp --- 
// 
// Filename: XmlParser.cpp
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 09:18:23 2008 (+0200)
// Version: 
// Last-Updated: Thu Nov 27 09:18:26 2008 (+0200)
//           By: Caner Candan
//     Update #: 1
// URL: 
// Keywords: 
// Compatibility: 
// 
// 

// Commentary: 
// 
// 
// 
// 

// Change log:
// 
// 
// 
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 3, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; see the file COPYING.  If not, write to
// the Free Software Foundation, Inc., 51 Franklin Street, Fifth
// Floor, Boston, MA 02110-1301, USA.

// 
// 

// Code:

#include <iostream>
#include <sstream>
#include "XmlParser.h"

XmlParser::XmlParser(const std::string& filename)
  : _filename(filename)
{
  ::xmlInitParser();
  this->_doc = ::xmlParseFile(this->_filename.c_str());
  if (!this->_doc)
    {
      std::cerr << "errror - xml file configuration invalid" << std::endl;
      exit(-1);
    }
  this->_root = ::xmlDocGetRootElement(this->_doc);
  if (!this->_root)
    {
      ::xmlFreeDoc(this->_doc);
      std::cerr << "error - xml file configuration is empty" << std::endl;
      exit(-1);
    }
  ::xmlXPathInit();
  this->_ctxt = ::xmlXPathNewContext(_doc);
  if (!this->_ctxt)
    {
      ::xmlFreeDoc(this->_doc);
      std::cerr << "error - can't create xml path context" << std::endl;
      exit(-1);
    }
}

XmlParser::~XmlParser()
{
  ::xmlFreeDoc(this->_doc);
  ::xmlXPathFreeContext(this->_ctxt);
}

XmlParser::listAttribute	XmlParser::xmlGetParam(const std::string& path)
{
  listAttribute		mapAttr;
  xmlXPathObjectPtr	xpath = this->_xPath(path);
  xmlNodePtr		node = xpath->nodesetval->nodeTab[0];
  xmlAttrPtr		attr = node->properties;

  while (attr != NULL)
    {
      std::string	key((char*)attr->name);
      std::string	val((char*)attr->children->content);

      mapAttr[key] = val;
      attr = attr->next;
    }
  return (mapAttr);
}

std::string	XmlParser::xmlGetParam(const std::string& path,
				       const std::string& sAttr)
{
  xmlXPathObjectPtr	xpath = this->_xPath(path);
  xmlNodePtr		node = xpath->nodesetval->nodeTab[0];
  xmlAttrPtr		attr = node->properties;

  while (attr != NULL)
    {
      std::string	key((char*)attr->name);
      std::string	val((char*)attr->children->content);

      if (key == sAttr)
	return (val);
    }
  return ("");
}

XmlParser::listParam	XmlParser::xmlGetListParam(const std::string& path)
{
  listParam		listParam;
  listAttribute		mapAttr;
  xmlXPathObjectPtr	xpath = this->_xPath(path);

  for (int i = 0; i < xpath->nodesetval->nodeNr; i++)
    {
      xmlNodePtr	node = xpath->nodesetval->nodeTab[i];

      node = node->children;
      while (node != NULL)
	{
	  if (node->type == XML_ELEMENT_NODE)
	    {
	      xmlAttrPtr	attr = node->properties;

	      while (attr != NULL)
		{
		  std::string	key((char*)attr->name);
		  std::string	val((char*)attr->children->content);

		  mapAttr[key] = val;
		  attr = attr->next;
		}
	      listParam.push_back(mapAttr);
	    }
	  node = node->next;
	}
    }
  //  xmlXPathFreeObject(xpath);
  return (listParam);
}

xmlXPathObjectPtr	XmlParser::_xPath(const std::string& path)
{
  xmlXPathObjectPtr	xpath;

  if (!(xpath = ::xmlXPathEvalExpression((xmlChar*)path.c_str(),
					 this->_ctxt)))
    std::cerr << "error - can't evaluate xpath expression"
	      << std::endl;
  else
    if (xpath->type != XPATH_NODESET)
      std::cerr << "error: can't find [" << path
		<< "] content" << std::endl;
  return (xpath);
}

// 
// XmlParser.cpp ends here
