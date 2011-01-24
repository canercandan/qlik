// Select.cpp --- 
// 
// Filename: Select.cpp
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 09:14:11 2008 (+0200)
// Version: 
// Last-Updated: Thu Nov 27 09:14:14 2008 (+0200)
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

#include <sys/select.h>
#include <iostream>
#include "Select.h"
#include "Config.h"
#include "SocketServer.h"
#include "SocketClient.h"
#include "State.h"
#include "Protocole.h"
#include "Action.h"
#include "Signal.h"

Select::Select(Server* server)
  : _server(server)
{
  Signal*	signal = Signal::getInstance();

  signal->addCallback(Signal::INT, Signal::HIGH, this,
		      static_cast<ISignalManager::callback>(&Select::signal));
}

Select::~Select()
{}

void	Select::start(void)
{
  Config*	config = Config::getInstance();

  _addServer(config->getPort());

  try
    {
      fd_set	fdRead;
      fd_set	fdWrite;
      int	fdMax;
      State*	state = State::getInstance();

      while (state->getLoopState() == State::LOOP_START)
	{
	  FD_ZERO(&fdRead);
	  FD_ZERO(&fdWrite);
	  fdMax = 0;
	  _setFd(fdRead, fdWrite, fdMax);
	  if (::select(fdMax + 1, &fdRead, &fdWrite,
		       NULL, NULL) < 0)
	    throw true;
	  _issetFd(fdRead, fdWrite);
	}
      if (config->isVerbose())
	std::cout << std::endl
		  << "Server stopped." << std::endl;
    }
  catch (bool)
    {
      if (config->isVerbose())
	std::cout << "Select: select error" << std::endl;
    }
}

void	Select::signal()
{
  if (Config::getInstance()->isVerbose())
    std::cout << "Select signal" << std::endl;

  State*	state = State::getInstance();

  state->setLoopState(State::LOOP_STOP);
}

void	Select::_addServer(int port)
{
  SocketServer*	ss = new SocketServer(port);
  Client*	client = new Client(ss, Client::SERVER);

  Server::listClients&	listClients = _server->getListClients();

  listClients.push_back(client);
}

void	Select::_addClient(Client* server)
{
  SocketClient*	sc = new SocketClient(server->socket()->socket());
  Client*	client = new Client(sc, Client::CLIENT);

  Server::listClients&	listClients = _server->getListClients();

  listClients.push_back(client);

  client->appendBufWrite(WELCOME);
  client->appendBufWrite(NL);
}

void	Select::_setFd(fd_set& fdRead, fd_set& fdWrite, int& fdMax)
{
  Server::listClients&	listClients = _server->getListClients();

  for (Server::listClients::iterator
	 it = listClients.begin(),
	 end = listClients.end();
       it != end; ++it)
    {
      Client*	client = *it;
      Socket*	socket = client->socket();

      if (!socket->getStatus())
	{
	  delete client;
	  listClients.erase(it);
	  continue;
	}

      FD_SET(socket->socket(), &fdRead);

      if (!client->getBufWrite().empty())
	FD_SET(socket->socket(), &fdWrite);

      if (fdMax < socket->socket())
	fdMax = socket->socket();
    }
}

void	Select::_issetFd(fd_set& fdRead, fd_set& fdWrite)
{
  Server::listClients&	listClients = _server->getListClients();

  for (Server::listClients::const_iterator
	 it = listClients.begin(),
	 end = listClients.end();
       it != end; ++it)
    {
      Client*	client = *it;
      Socket*	socket = client->socket();

      if (!socket->getStatus())
	continue;

      if (FD_ISSET(socket->socket(), &fdRead))
	{
	  if (client->getType() == Client::SERVER)
	    _serverRead(client);
	  else
	    _clientRead(client);
	}

      if (FD_ISSET(socket->socket(), &fdWrite))
	_clientWrite(client);
    }
}

void	Select::_serverRead(Client* server)
{
  if (Config::getInstance()->isVerbose())
    std::cout << "Select: server read" << std::endl;

  _addClient(server);
}

void	Select::_clientRead(Client* client)
{
  Socket*	socket = client->socket();

  if (Config::getInstance()->isVerbose())
    std::cout << "Select: ["
	      << socket->socket()
	      << "] client read" << std::endl;

  client->clearBufRead();
  client->appendBufRead(socket->recv());

  State*	state = State::getInstance();

  if (state->getProcessState() == State::PROCESS_BREAK &&
      !(client->getRight() & RIGHT_SERVER))
    return;

  Action	action(_server, client);

  action.execute();
}

void	Select::_clientWrite(Client* client)
{
  Socket*	socket = client->socket();

  if (Config::getInstance()->isVerbose())
    std::cout << "Select: ["
	      << socket->socket()
	      << "] client write" << std::endl;

  socket->send(client->getBufWrite());
  client->clearBufWrite();
}

// 
// Select.cpp ends here
