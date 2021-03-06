// Config.h --- 
// 
// Filename: Config.h
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 01:46:12 2008 (+0200)
// Version: 
// Last-Updated: Thu Nov 27 15:17:46 2008 (+0200)
//           By: Caner Candan
//     Update #: 17
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
// 27-Nov-2008    Caner Candan  
//    Last-Updated: Thu Nov 27 15:17:29 2008 (+0200) #16 (Caner Candan)
//    delete default filename FILE_CONFIG, create fillFromFile function
// 27-Nov-2008    Caner Candan  
//    Last-Updated: Thu Nov 27 12:05:17 2008 (+0200) #5 (Caner Candan)
//    server.xml -> config.xml
// 27-Nov-2008    Caner Candan  
//    Last-Updated: Thu Nov 27 01:46:15 2008 (+0200) #1 (Caner Candan)
//    ../server.xml -> server.xml
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

#ifndef __CONFIG_H__
# define __CONFIG_H__

# include <string>
# include "Singleton.hpp"

class	Config : public Singleton<Config>
{
  friend class	Singleton<Config>;
public:
  void	fillFromFile(const std::string& filename);

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

// 
// Config.h ends here
