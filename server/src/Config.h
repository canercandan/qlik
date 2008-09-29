//
// Config.h for server in /home/candan_c/cu/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Sep 28 22:51:11 2008 caner candan
// Last update Mon Sep 29 14:23:29 2008 caner candan
//

#ifndef __CONFIG_H__
# define __CONFIG_H__

# include <string>
# include "XmlParser.h"
# include "Singleton.hpp"

# define FILE_CONFIG	"../server.xml"

class	Config : public XmlParser,
		 public Singleton<Config>
{
  friend class	Singleton<Config>;
public:
  const std::string&	getDatabase(void){return (_database);}
private:
  void	_setDatabase(const std::string& database){_database = database;}
private:
  std::string	_database;
public:
  const int&	getPort(void){return (_port);}
private:
  void	_setPort(const int& port){_port = port;}
private:
  int	_port;
public:
  bool	isDaemon(void){return (_daemon);}
private:
  void	_setDaemon(bool daemon){_daemon = daemon;}
private:
  bool	_daemon;
public:
  bool	isVerbose(void){return (_verbose);}
private:
  void	_setVerbose(bool verbose){_verbose = verbose;}
private:
  bool	_verbose;
private:
  Config();
};

#endif // !__CONFIG_H__
