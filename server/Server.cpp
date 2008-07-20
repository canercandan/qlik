//
// Server.cpp for Server in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Fri Jul 11 21:40:50 2008 caner candan
// Last update Thu Jul 17 20:12:49 2008 caner candan
//

#include <sys/select.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "Server.h"
#include "Client.h"
#include "SocketServer.h"
#include "SocketClient.h"
#include "Service.h"
#include "ServiceWeb.h"
#include "ServiceStream.h"

Server::Actions	Server::actions[NB_ACTIONS] = {
  {actLogin, MESG_EMPTY},
  {actLogout, MESG_OK},
  {actCreate, MESG_EMPTY},
  {actStatus, MESG_EMPTY},
  {actClients, MESG_EMPTY},
  {actAccounts, MESG_EMPTY},
  {actMessage, MESG_EMPTY},
  {actServices, MESG_EMPTY},
  {actCreateService, MESG_EMPTY}
};

Server::Server(bool verbose /*= false*/)
  : _verbose(verbose)
{}

Server::Server(const Server& s)
{*this = s;}

Server::~Server()
{
  destroyListClients();
}

Server&	Server::operator=(const Server& s)
{
  if (this != &s)
    {
      this->_clients = s._clients;
      this->_verbose = s._verbose;
    }
  return (*this);
}

void	Server::destroyListClients()
{
  listClients::iterator	it = this->_clients.begin();
  listClients::iterator	end = this->_clients.end();

  while (it != end)
    {
      if (*it != NULL)
	{
	  ::free(*it);
	  *it = NULL;
	}
      ++it;
    }
}

void		Server::addServer(int port)
{
  Client	*client;
  SocketServer	*ss;

  ss = new SocketServer(port, this->_verbose);
  client = new Client(ss, Client::SERVER);
  this->_clients.push_back(client);
}

void		Server::addClient(Client *server)
{
  Client	*client;
  SocketClient	*sc;

  sc = new SocketClient(server->getSocket()->getSocket(), true);
  client = new Client(sc, Client::CLIENT);
  this->_clients.push_back(client);
  client->setBufWrite(MESG_WELCOME);
}

void	Server::setFd(fd_set& fdRead, fd_set& fdWrite, int& fdMax)
{
  listClients::const_iterator	it;
  listClients::const_iterator	end = this->_clients.end();

  for (it = this->_clients.begin(); it != end; ++it)
    {
      if (!(*it)->getSocket()->getStatus())
	continue;
      FD_SET((*it)->getSocket()->getSocket(), &fdRead);
      if (!(*it)->getBufWrite().empty())
	FD_SET((*it)->getSocket()->getSocket(), &fdWrite);
      if (fdMax < (*it)->getSocket()->getSocket())
	fdMax = (*it)->getSocket()->getSocket();
    }
}

const Server::listClients&	Server::getListClients(void) const
{
  return (this->_clients);
}

void	Server::issetFd(fd_set& fdRead, fd_set& fdWrite)
{
  listClients::const_iterator	it;
  listClients::const_iterator	end = this->_clients.end();

  for (it = this->_clients.begin(); it != end; ++it)
    {
      if (!(*it)->getSocket()->getStatus())
	continue;
      if (FD_ISSET((*it)->getSocket()->getSocket(), &fdRead))
	if ((*it)->getType() == Client::SERVER)
	  this->serverRead(*it);
	else
	  this->clientRead(*it);
      if (FD_ISSET((*it)->getSocket()->getSocket(), &fdWrite))
	this->clientWrite(*it);
    }
}

void		Server::loopServer(void)
{
  fd_set	fdRead;
  fd_set	fdWrite;
  int		fdMax;

  try
    {
      while (42)
	{
	  FD_ZERO(&fdRead);
	  FD_ZERO(&fdWrite);
	  fdMax = 0;
	  this->setFd(fdRead, fdWrite, fdMax);
	  if (::select(fdMax + 1, &fdRead, &fdWrite,
		       NULL, NULL) < 0)
	    throw true;
	  this->issetFd(fdRead, fdWrite);
	}
    }
  catch (bool)
    {
      std::cout << this->head()
		<< "select error" << std::endl;
    }
}

void	Server::serverRead(Client *server)
{
  if (this->_verbose)
    std::cout << this->head()
	      << "server read" << std::endl;
  addClient(server);
}

void	Server::clientRead(Client *client)
{
  if (this->_verbose)
    std::cout << this->head() << " ["
	      << client->getSocket()->getSocket()
	      << "] client read" << std::endl;
  client->clearBufRead();
  client->setBufRead(client->getSocket()->recv());
  this->executeAction(client);
}

void	Server::clientWrite(Client *client)
{
  if (this->_verbose)
    std::cout << this->head() << " ["
	      << client->getSocket()->getSocket()
	      << "] client write" << std::endl;
  client->getSocket()->send(client->getBufWrite());
  client->clearBufWrite();
}

void	Server::executeAction(Client *client)
{
  std::stringstream	ss(client->getBufRead());
  int			action;
  
  ss >> action;
  if (action >= 0 && action < NB_ACTIONS)
    if (actions[action].func)
      {
	ss.str(MESG_EMPTY);
	ss << action << ' ';
	client->setBufWrite(ss.str());
	actions[action].func(this, client);
	if (!actions[action].retMesg.empty())
	  client->setBufWrite(actions[action].retMesg);
	return;
      }
  client->setBufWrite(MESG_KO);
}

bool	Server::existLogin(const std::string& login)
{
  std::fstream	file(ACCOUNT_FILE);
  std::string	loginFile;
  std::string	passwdFile;

  while (!file.eof())
    {
      file >> loginFile >> passwdFile;
      if (loginFile == login)
	{
	  file.close();
	  return (true);
	}
    }
  file.close();
  return (false);
}

bool	Server::existLoginPasswd(const std::string& login,
				 const std::string& passwd,
				 int& creditFile)
{
  std::fstream	file(ACCOUNT_FILE);
  std::string	loginFile;
  std::string	passwdFile;

  while (!file.eof())
    {
      file >> loginFile >> passwdFile >> creditFile;
      if (loginFile == login &&
	  passwdFile == passwd)
	{
	  file.close();
	  return (true);
	}
    }
  file.close();
  return (false);
}

bool	Server::alreadyConnected(const std::string& login,
				 Server *server)
{
  listClients::const_iterator	it;
  listClients::const_iterator	end = server->getListClients().end();

  for (it = server->getListClients().begin(); it != end; ++it)
    if ((*it)->isConnected())
      if ((*it)->getLogin() == login)
	return (true);
  return (false);
}

Client	*Server::findClient(const std::string& login,
			    Server *server)
{
  listClients::const_iterator	it;
  listClients::const_iterator	end = server->getListClients().end();

  for (it = server->getListClients().begin(); it != end; ++it)
    if ((*it)->isConnected())
      if ((*it)->getLogin() == login)
	return (*it);
  return (NULL);
}

bool	Server::notConnected(Client *client)
{
  if (!client->isConnected())
    {
      client->setBufWrite(MESG_KO);
      return (true);
    }
  return (false);
}

void	Server::actLogin(Server *server, Client *client)
{
  std::stringstream	ss(client->getBufRead());
  std::string		action;
  std::string		login;
  std::string		passwd;
  int			credit;

  ss >> action >> login >> passwd;
  credit = 0;
  if (login.empty() || passwd.empty() ||
      !existLoginPasswd(login, passwd, credit) ||
      alreadyConnected(login, server))
    {
      client->setBufWrite(MESG_KO);
      return;
    }
  client->setLogin(login);
  client->setCredit(credit);
  client->setBufWrite(MESG_OK);
}

void	Server::actLogout(Server*, Client *client)
{
  client->setLogin(MESG_EMPTY);
}

void	Server::actCreate(Server*, Client *client)
{
  std::stringstream	ss(client->getBufRead());
  std::string		action;
  std::string		login;
  std::string		passwd;
  std::fstream		file;

  ss >> action >> login >> passwd;
  if (login.empty() || passwd.empty() ||
      existLogin(login))
    {
      client->setBufWrite(MESG_KO);
      return;
    }
  file.open(ACCOUNT_FILE, std::fstream::out | std::fstream::app);
  file << login << '\t' << passwd << '\t' << 0 << '\n';
  file.close();
  client->setBufWrite(MESG_OK);
}

void	Server::actStatus(Server*, Client *client)
{
  if (!notConnected(client))
    client->setBufWrite(MESG_OK);
}

void	Server::actClients(Server *server, Client *client)
{
  listClients::const_iterator	it;
  listClients::const_iterator	end = server->getListClients().end();

  if (notConnected(client))
    return;
  client->setBufWrite(MESG_BEGIN);
  for (it = server->getListClients().begin(); it != end; ++it)
    if ((*it)->isConnected())
      client->setBufWrite((*it)->getLogin() + '\n');
  client->setBufWrite(MESG_END);
}

void	Server::actAccounts(Server*, Client *client)
{
  std::fstream		file(ACCOUNT_FILE);
  std::stringstream	ss;
  std::string		loginFile;
  std::string		passwdFile;
  std::string		creditFile;

  if (notConnected(client))
    return;
  client->setBufWrite(MESG_BEGIN);
  while (!file.eof())
    {
      file >> loginFile >> passwdFile >> creditFile;
      if (loginFile.empty())
	continue;
      ss << loginFile << ' ' << creditFile << '\n';
      client->setBufWrite(ss.str());
      loginFile.clear();
      passwdFile.clear();
      creditFile.clear();
      ss.str(MESG_EMPTY);
    }
  file.close();
  client->setBufWrite(MESG_END);
}

void	Server::actMessage(Server *server, Client *client)
{
  std::string	str(client->getBufRead());
  std::string	action;
  std::string	login;
  std::string	message;
  size_t	separator;
  Client	*to;

  if (notConnected(client))
    return;
  separator = str.find(' ');
  action = str.substr(0, separator);
  str = str.substr(separator + 1);
  separator = str.find(' ');
  login = str.substr(0, separator);
  message = str.substr(separator + 1);
  if (login.empty() || message.empty() ||
      !(to = findClient(login, server)))
    {
      client->setBufWrite(MESG_KO);
      return;
    }
  to->setBufWrite(client->getLogin() + ' ' + message);
  client->setBufWrite(MESG_OK);
}

void	Server::actServices(Server*, Client *client)
{
  Client::listServices::const_iterator	it;
  Client::listServices::const_iterator	end = client->getListServices().end();
  std::stringstream			ss;

  if (notConnected(client))
    return;
  client->setBufWrite(MESG_BEGIN);
  for (it = client->getListServices().begin(); it != end; ++it)
    {
      if ((*it)->getType() == Service::WEB)
	ss << "WEB"
	   << ' ' << ((ServiceWeb*)(*it))->getOffer().space
	   << ' ' << ((ServiceWeb*)(*it))->getOffer().nbDb
	   << ' ' << (*it)->getName()
	   << ' ' << (*it)->getPasswd()
	   << ' ' << ((ServiceWeb*)(*it))->getDomain()
	   << '\n';
      else
	ss << "STREAM"
	   << ' ' << ((ServiceStream*)(*it))->getOffer().slots
	   << ' ' << ((ServiceStream*)(*it))->getOffer().nbBits
	   << ' ' << (*it)->getName()
	   << ' ' << (*it)->getPasswd()
	   << '\n';
      client->setBufWrite(ss.str());
      ss.str(MESG_EMPTY);
    }
  client->setBufWrite(MESG_END);
}

void	Server::actCreateService(Server*, Client *client)
{
  std::stringstream	ss(client->getBufRead());
  std::string		action;
  int			service;
  int			offerId;
  std::string		name;
  std::string		passwd;
  std::string		domain;

  if (notConnected(client))
    return;
  offerId = 0;
  ss >> action >> service >> offerId >> name >> passwd;
  if (service != Service::WEB &&
      service != Service::STREAM)
    {
      client->setBufWrite(MESG_KO);
      return;
    }
  if (service == Service::WEB)
    {
      ss >> domain;
      client->addService(new ServiceWeb(name, passwd, domain,
					(ServiceWeb::OfferId)offerId));
    }
  else
    client->addService(new ServiceStream(name, passwd,
					 (ServiceStream::OfferId)offerId));
  client->setBufWrite(MESG_OK);
}

std::string	Server::head(void)
{
  std::stringstream	ss;

  ss << "Server: ";
  return (ss.str());
}
