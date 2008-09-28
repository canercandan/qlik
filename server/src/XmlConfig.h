//
// XmlConfig.h for server in /home/candan_c/cu/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Sep 28 22:51:11 2008 caner candan
// Last update Sun Sep 28 22:51:11 2008 caner candan
//

#ifndef __XMLCONFIG_H__
# define __XMLCONFIG_H__

# include "XmlParser.h"
# include "Singleton.hpp"

# define FILE_CONFIG	"../server.xml"

class	XmlConfig : public XmlParser,
		    public Singleton<XmlConfig>
{
private:
  XmlConfig();
};

#endif // !__XMLCONFIG_H__
