// XmlParser.h --- 
// 
// Filename: XmlParser.h
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 09:18:28 2008 (+0200)
// Version: 
// Last-Updated: Thu Nov 27 09:18:30 2008 (+0200)
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

#ifndef __XMLPARSER_H__
# define __XMLPARSER_H__

# include <libxml/parser.h>
# include <libxml/xpath.h>
# include <string>
# include <list>
# include <map>

class	XmlParser
{
public:
  typedef std::map<std::string, std::string>	listAttribute;
  typedef std::list<listAttribute>		listParam;
public:
  XmlParser(const std::string& filename);
  ~XmlParser();

  listAttribute	xmlGetParam(const std::string& path);
  std::string	xmlGetParam(const std::string& path,
			    const std::string& attr);
  listParam	xmlGetListParam(const std::string& path);
private:
  xmlXPathObjectPtr	_xPath(const std::string& path);
private:
  std::string		_filename;
  xmlDocPtr		_doc;
  xmlNodePtr		_root;
  xmlXPathContextPtr	_ctxt;
};

#endif // !__XMLPARSER_H__

// 
// XmlParser.h ends here
