//
// Server.cpp for Server in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Fri Jul 11 21:40:50 2008 caner candan
// Last update Mon Oct 27 15:32:30 2008 caner candan
//

#include <string>
#include <iostream>
#include "Server.h"
#include "Client.h"
#include "Signal.h"
#include "Config.h"
#include "Select.h"

Server::Server()
  : _head("Server: ")
{
  Signal*	signal = Signal::getInstance();

  signal->addCallback(Signal::INT, Signal::LOW, this,
		      static_cast<ISignalManager::callback>
		      (&Server::signal));
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
      if (*it)
	{
	  delete *it;
	  *it = NULL;
	}
    }
}
