//
// Config.h for server in /home/candan_c/cu/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Sep 28 22:51:11 2008 caner candan
// Last update Mon Sep 29 12:22:51 2008 caner candan
//

#ifndef __CONFIG_H__
# define __CONFIG_H__

# include "XmlParser.h"
# include "Singleton.hpp"

# define FILE_CONFIG	"../server.xml"

class	Config : public XmlParser,
		 public Singleton<Config>
{
  friend class	Singleton<Config>;
private:
  Config();
};

#endif // !__CONFIG_H__
