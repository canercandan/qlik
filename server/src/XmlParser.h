//
// XmlParser.h for server in /home/candan_c/cu/rendu/ekzay/server/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Sep 28 02:38:15 2008 caner candan
// Last update Sun Sep 28 22:45:33 2008 caner candan
//

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
