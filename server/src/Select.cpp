//
// Select.cpp for server in /home/candan_c/cu/rendu/qlik/server/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Oct 26 17:10:49 2008 caner candan
// Last update Mon Oct 27 18:23:20 2008 caner candan
//

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
  : _server(server), _head("Select: ")
{
  Signal*	signal = Signal::getInstance();

  signal->addCallback(Signal::INT, Signal::HIGH, this,
		      static_cast<ISignalManager::callback>
		      (&Select::signal));
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
	std::cout << _head
		  << "select error" << std::endl;
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
  SocketClient*	sc = new SocketClient(server->getSocket()->getSocket());
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

      if (!client->getSocket()->getStatus())
	{
	  delete client;
	  listClients.erase(it);
	  continue;
	}

      FD_SET(client->getSocket()->getSocket(), &fdRead);

      if (!client->getBufWrite().empty())
	FD_SET(client->getSocket()->getSocket(), &fdWrite);

      if (fdMax < client->getSocket()->getSocket())
	fdMax = client->getSocket()->getSocket();
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

      if (!client->getSocket()->getStatus())
	continue;

      if (FD_ISSET(client->getSocket()->getSocket(), &fdRead))
	{
	  if (client->getType() == Client::SERVER)
	    _serverRead(client);
	  else
	    _clientRead(client);
	}

      if (FD_ISSET(client->getSocket()->getSocket(), &fdWrite))
	_clientWrite(client);
    }
}

void	Select::_serverRead(Client* server)
{
  if (Config::getInstance()->isVerbose())
    std::cout << _head
	      << "server read" << std::endl;

  _addClient(server);
}

void	Select::_clientRead(Client* client)
{
  if (Config::getInstance()->isVerbose())
    std::cout << _head << " ["
	      << client->getSocket()->getSocket()
	      << "] client read" << std::endl;

  client->clearBufRead();
  client->appendBufRead(client->getSocket()->recv());

  State*	state = State::getInstance();

  if (state->getProcessState() == State::PROCESS_BREAK)
    return;

  Action	action(_server, client);

  action.execute();
}

void	Select::_clientWrite(Client* client)
{
  if (Config::getInstance()->isVerbose())
    std::cout << _head << " ["
	      << client->getSocket()->getSocket()
	      << "] client write" << std::endl;

  client->getSocket()->send(client->getBufWrite());
  client->clearBufWrite();
}
