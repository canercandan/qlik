// Server.cpp --- 
// 
// Filename: Server.cpp
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 09:14:21 2008 (+0200)
// Version: 
// Last-Updated: Sun Dec 28 12:42:03 2008 (+0200)
//           By: Caner Candan
//     Update #: 13
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

#include <string>
#include <iostream>
#include "Server.h"
#include "Signal.h"
#include "Config.h"
#include "Select.h"

Server::Server()
{
  Signal*	signal = Signal::getInstance();

  signal->addCallback(Signal::INT, Signal::LOW, this,
		      static_cast<ISignalManager::callback>(&Server::signal));
}

Server::~Server()
{
  _destroyListClients();
}

void	Server::start()
{
  Select	select(this);

  select.start();
}

void	Server::signal()
{
  if (Config::getInstance()->isVerbose())
    std::cout << "Server signal" << std::endl;

  _destroyListClients();
}

Client*	Server::findClient(const std::string& login)
{
  for (listClients::const_iterator
	 it = _clients.begin(),
	 end = _clients.end();
       it != end; ++it)
    {
      Client*	client = *it;

      if (client->isConnected())
	if (client->getLogin() == login)
	  return (client);
    }
  return (NULL);
}

Client*	Server::findClient(const int id)
{
  for (listClients::const_iterator
	 it = _clients.begin(),
	 end = _clients.end();
       it != end; ++it)
    {
      Client*	client = *it;

      if (client->isConnected())
	if (client->getId() == id)
	  return (client);
    }
  return (NULL);
}

Server::listClients&	Server::getListClients()
{
  return (_clients);
}

Server::mapStreamPid&	Server::getMapStreamPid()
{
  return (_mapStreamPid);
}

void	Server::_destroyListClients()
{
  for (listClients::iterator
	 it = _clients.begin(),
	 end = _clients.end();
       it != end; ++it)
    {
      Client*	client = *it;

      if (!client)
	continue;

      delete client;
      *it = NULL;
    }
}

// 
// Server.cpp ends here
