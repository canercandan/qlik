//
// Config.cpp for server in /home/candan_c/cu/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Sep 28 22:51:09 2008 caner candan
// Last update Mon Sep 29 14:20:59 2008 caner candan
//

#include <sstream>
#include "Config.h"

Config::Config()
  : XmlParser(FILE_CONFIG)
{
  _setDatabase(xmlGetParam("//server/database", "path"));

  std::stringstream	ss(xmlGetParam("//server/listen", "port"));
  int			port;

  ss >> port;

  _setPort(port);
  _setDaemon(xmlGetParam("//server/daemon", "enabled") == "true");
  _setVerbose(xmlGetParam("//server/verbose", "enabled") == "true");
}
