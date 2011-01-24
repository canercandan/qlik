// Server.h --- 
// 
// Filename: Server.h
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 09:15:48 2008 (+0200)
// Version: 
// Last-Updated: Wed Dec  3 02:28:17 2008 (+0200)
//           By: Caner Candan
//     Update #: 4
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

#ifndef __SERVER_H__
# define __SERVER_H__

# include <sys/types.h>
# include <list>
# include <map>
# include <string>
# include "Client.h"
# include "ISignalManager.h"

class	Server : public ISignalManager
{
public:
  typedef std::list<Client*>	listClients;

  typedef std::map<std::string, pid_t>		mapClientPid;
  typedef std::map<std::string, mapClientPid>	mapStreamPid;
public:
  Server();
  ~Server();

  void	start();

  Client*	findClient(const std::string& login);
  Client*	findClient(const int id);

  listClients&	getListClients();
  mapStreamPid&	getMapStreamPid();

  void	signal();
private:
  void	_destroyListClients();
private:
  listClients	_clients;
  mapStreamPid	_mapStreamPid;
};

#endif // !__SERVER_H__

// 
// Server.h ends here
