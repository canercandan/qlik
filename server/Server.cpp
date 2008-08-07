//
// Server.cpp for Server in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Fri Jul 11 21:40:50 2008 caner candan
// Last update Thu Aug  7 13:18:49 2008 caner candan
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

Server::Actions	Server::actions[] = {
  {LOGIN, actLogin, MESG_EMPTY},
  {LOGOUT, actLogout, MESG_OK},
  {CREATE, actCreate, MESG_EMPTY},
  {STATUS, actStatus, MESG_EMPTY},
  {CLIENTS, actClients, MESG_EMPTY},
  {ACCOUNTS, actAccounts, MESG_EMPTY},
  {MESSAGE, actMessage, MESG_EMPTY},
  {SERVICES_WEB, actServicesWeb, MESG_EMPTY},
  {SERVICES_STREAM, actServicesStream, MESG_EMPTY},
  {OFFER_WEB, actOfferWeb, MESG_EMPTY},
  {OFFER_STREAM, actOfferStream, MESG_EMPTY},
  {CREATE_OFFER_WEB, actCreateOfferWeb, MESG_EMPTY},
  {CREATE_OFFER_STREAM, actCreateOfferStream, MESG_EMPTY},
  {CREATE_WEB, actCreateWeb, MESG_EMPTY},
  {CREATE_STREAM, actCreateStream, MESG_EMPTY},
  {NEWS, actNews, MESG_EMPTY},
  {NEWS_DETAIL, actNewsDetail, MESG_EMPTY},
  {MESG_EMPTY, NULL, MESG_EMPTY}
};

Server::Server(bool verbose /*= false*/)
  : _verbose(verbose)
{
  _sql.Open("db/server.db");
}

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
  client->setBufWrite(WELCOME);
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
  std::string		action;
  int			i;
  
  ss >> action;
  for (i = 0; actions[i].func; i++)
    if (actions[i].keyword == action)
      {
	ss.str(MESG_EMPTY);
	ss << action << ' ';
	client->setBufWrite(ss.str());
	actions[i].func(this, client);
	if (!actions[i].retMesg.empty())
	  client->setBufWrite(actions[i].retMesg);
	return;
      }
  client->setBufWrite(MESG_KO);
}

bool	Server::existLogin(const std::string& login)
{
  SQLiteStatement	*stmt;

  stmt = this->_sql.Statement("select 1 "
			      "from users "
			      "where username = ? "
			      "limit 1;");
  stmt->Bind(0, login);
  while (stmt->NextRow())
    {
      delete stmt;
      return (true);
    }
  delete stmt;
  return (false);
}

bool	Server::existLoginPasswd(const std::string& login,
				 const std::string& passwd)
{
  SQLiteStatement	*stmt;

  stmt = this->_sql.Statement("select 1 "
			      "from users "
			      "where username = ? "
			      "and password = ? "
			      "limit 1;");
  stmt->Bind(0, login);
  stmt->Bind(1, passwd);
  while (stmt->NextRow())
    {
      delete stmt;
      return (true);
    }
  delete stmt;
  return (false);
}

bool	Server::alreadyConnected(const std::string& login)
{
  listClients::const_iterator	it;
  listClients::const_iterator	end = this->getListClients().end();

  for (it = this->getListClients().begin(); it != end; ++it)
    if ((*it)->isConnected())
      if ((*it)->getLogin() == login)
	return (true);
  return (false);
}

Client	*Server::findClient(const std::string& login)
{
  listClients::const_iterator	it;
  listClients::const_iterator	end = this->getListClients().end();

  for (it = this->getListClients().begin(); it != end; ++it)
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
  SQLiteStatement	*stmt;
  std::stringstream	ss(client->getBufRead());
  std::string		action;
  std::string		login;
  std::string		passwd;

  ss >> action >> login >> passwd;
  if (login.empty() || passwd.empty() ||
      !server->existLoginPasswd(login, passwd) ||
      server->alreadyConnected(login))
    {
      client->setBufWrite(MESG_KO);
      return;
    }
  stmt = server->_sql.Statement("select users.id, users.username, "
				"credit.value " 
				"from users, credit "
				"where users.id = credit.id_user "
				"and username = ? "
				"limit 1;");
  stmt->Bind(0, login);
  while (stmt->NextRow())
    {
      client->setId(stmt->ValueInt(0));
      client->setLogin(stmt->ValueString(1));
      client->setCredit(stmt->ValueInt(2));
    }
  client->setBufWrite(MESG_OK);
  delete stmt;
}

void	Server::actLogout(Server*, Client *client)
{
  client->setLogin(MESG_EMPTY);
}

void	Server::actCreate(Server* server, Client *client)
{
  SQLiteStatement	*stmt;
  std::stringstream	ss(client->getBufRead());
  std::string		action;
  std::string		login;
  std::string		passwd;

  ss >> action >> login >> passwd;
  if (login.empty() || passwd.empty() ||
      server->existLogin(login))
    {
      client->setBufWrite(MESG_KO);
      return;
    }
  stmt = server->_sql.Statement("insert into users "
				"values(NULL, ?, ?);");
  stmt->Bind(0, login);
  stmt->Bind(1, passwd);
  stmt->Execute();
  delete stmt;
  stmt = server->_sql.Statement("insert into credit "
				"values(last_insert_rowid(), 0);");
  stmt->Execute();
  client->setBufWrite(MESG_OK);
  delete stmt;
}

void	Server::actStatus(Server* server, Client *client)
{
  if (!server->notConnected(client))
    client->setBufWrite(MESG_OK);
}

void	Server::actClients(Server *server, Client *client)
{
  listClients::const_iterator	it;
  listClients::const_iterator	end = server->getListClients().end();

  if (server->notConnected(client))
    return;
  client->setBufWrite(MESG_BEGIN);
  for (it = server->getListClients().begin(); it != end; ++it)
    if ((*it)->isConnected())
      client->setBufWrite((*it)->getLogin() + '\n');
  client->setBufWrite(MESG_END);
}

void	Server::actAccounts(Server *server, Client *client)
{
  SQLiteStatement	*stmt;
  std::stringstream	ss;

  if (server->notConnected(client))
    return;
  client->setBufWrite(MESG_BEGIN);
  stmt = server->_sql.Statement("select username "
				"from users;");
  while (stmt->NextRow())
    {
      ss.str(MESG_EMPTY);
      ss << stmt->ValueString(0) << std::endl;
      client->setBufWrite(ss.str());
    }
  client->setBufWrite(MESG_END);
  delete stmt;
}

void	Server::actMessage(Server *server, Client *client)
{
  std::string	str(client->getBufRead());
  std::string	action;
  std::string	login;
  std::string	message;
  size_t	separator;
  Client	*to;

  if (server->notConnected(client))
    return;
  separator = str.find(' ');
  action = str.substr(0, separator);
  str = str.substr(separator + 1);
  separator = str.find(' ');
  login = str.substr(0, separator);
  message = str.substr(separator + 1);
  if (login.empty() || message.empty() ||
      !(to = server->findClient(login)))
    {
      client->setBufWrite(MESG_KO);
      return;
    }
  to->setBufWrite(std::string(MESSAGE) + ' ');
  to->setBufWrite(client->getLogin() + ' ' + message);
  client->setBufWrite(MESG_OK);
}

void	Server::actServicesWeb(Server* server, Client *client)
{
  SQLiteStatement	*stmt;
  std::stringstream	ss;

  if (server->notConnected(client))
    return;
  client->setBufWrite(MESG_BEGIN);
  stmt = server->_sql.Statement("select name "
				"from services_web;");
  while (stmt->NextRow())
    {
      ss.str(MESG_EMPTY);
      ss << stmt->ValueString(0) << std::endl;
      client->setBufWrite(ss.str());
    }
  client->setBufWrite(MESG_END);
  delete stmt;
}

void	Server::actServicesStream(Server* server, Client *client)
{
  SQLiteStatement	*stmt;
  std::stringstream	ss;

  if (server->notConnected(client))
    return;
  client->setBufWrite(MESG_BEGIN);
  stmt = server->_sql.Statement("select name "
				"from services_stream;");
  while (stmt->NextRow())
    {
      ss.str(MESG_EMPTY);
      ss << stmt->ValueString(0) << std::endl;
      client->setBufWrite(ss.str());
    }
  client->setBufWrite(MESG_END);
  delete stmt;
}

void	Server::actOfferWeb(Server* server, Client* client)
{
  SQLiteStatement	*stmt;
  std::stringstream	ss;

  if (server->notConnected(client))
    return;
  client->setBufWrite(MESG_BEGIN);
  stmt = server->_sql.Statement("select name "
				"from offer_web;");
  while (stmt->NextRow())
    {
      ss.str(MESG_EMPTY);
      ss << stmt->ValueString(0) << std::endl;
      client->setBufWrite(ss.str());
    }
  client->setBufWrite(MESG_END);
  delete stmt;
}

void	Server::actOfferStream(Server* server, Client* client)
{
  SQLiteStatement	*stmt;
  std::stringstream	ss;

  if (server->notConnected(client))
    return;
  client->setBufWrite(MESG_BEGIN);
  stmt = server->_sql.Statement("select name "
				"from offer_stream;");
  while (stmt->NextRow())
    {
      ss.str(MESG_EMPTY);
      ss << stmt->ValueString(0) << std::endl;
      client->setBufWrite(ss.str());
    }
  client->setBufWrite(MESG_END);
  delete stmt;
}

void	Server::actCreateOfferWeb(Server* server, Client* client)
{
  SQLiteStatement	*stmt;
  std::stringstream	ss(client->getBufRead());
  std::string		action;
  std::string		name;
  int			row;
  std::string		domain;
  int			space;
  int			nbDb;

  if (server->notConnected(client))
    return;
  row = 0;
  ss >> action >> name >> row >> domain;
  stmt = server->_sql.Statement("select space, nb_db "
				"from offer_web "
				"limit ?, 1;");
  stmt->Bind(0, row);
  if (stmt->NextRow())
    {
      space = stmt->ValueInt(0);
      nbDb = stmt->ValueInt(1);
      delete stmt;
      stmt = server->_sql.Statement("insert into services_web "
				    "values(NULL, ?, ?, ?, ?, ?, ?, ?);");
      stmt->Bind(0, client->getId());
      stmt->Bind(1, name);
      stmt->Bind(2, space);
      stmt->Bind(3, nbDb);
      stmt->Bind(4, domain);
      stmt->Bind(5, 1);
      stmt->Bind(6, 1);
      stmt->Execute();
      client->setBufWrite(MESG_OK);
    }
  else
    client->setBufWrite(MESG_KO);
  delete stmt;
}

void	Server::actCreateOfferStream(Server* server, Client* client)
{
  SQLiteStatement	*stmt;
  std::stringstream	ss(client->getBufRead());
  std::string		action;
  std::string		name;
  int			row;
  std::string		title;
  int			slots;
  int			bits;

  if (server->notConnected(client))
    return;
  row = 0;
  ss >> action >> name >> row >> title;
  stmt = server->_sql.Statement("select slots, bits "
				"from offer_stream "
				"limit ?, 1;");
  stmt->Bind(0, row);
  if (stmt->NextRow())
    {
      slots = stmt->ValueInt(0);
      bits = stmt->ValueInt(1);
      delete stmt;
      stmt = server->_sql.Statement("insert into services_stream "
				    "values(NULL, ?, ?, ?, ?, ?, ?, ?);");
      stmt->Bind(0, client->getId());
      stmt->Bind(1, name);
      stmt->Bind(2, slots);
      stmt->Bind(3, bits);
      stmt->Bind(4, title);
      stmt->Bind(5, 1);
      stmt->Bind(6, 1);
      stmt->Execute();
      client->setBufWrite(MESG_OK);
    }
  else
    client->setBufWrite(MESG_KO);
  delete stmt;
}

void	Server::actCreateWeb(Server* server, Client* client)
{
  SQLiteStatement	*stmt;
  std::stringstream	ss(client->getBufRead());
  std::string		action;
  std::string		name;
  int			space;
  int			nbDb;
  std::string		domain;

  if (server->notConnected(client))
    return;
  space = 0;
  nbDb = 0;
  ss >> action >> name >> space >> nbDb >> domain;
  if (name.empty() || !space || !nbDb || domain.empty())
    {
      client->setBufWrite(MESG_KO);
      return;
    }
  stmt = server->_sql.Statement("insert into services_web "
				"values(NULL, ?, ?, ?, ?, ?, ?, ?);");
  stmt->Bind(0, client->getId());
  stmt->Bind(1, name);
  stmt->Bind(2, space);
  stmt->Bind(3, nbDb);
  stmt->Bind(4, domain);
  stmt->Bind(5, 1);
  stmt->Bind(6, 1);
  stmt->Execute();
  client->setBufWrite(MESG_OK);
  delete stmt;
}

void	Server::actCreateStream(Server* server, Client* client)
{
  SQLiteStatement	*stmt;
  std::stringstream	ss(client->getBufRead());
  std::string		action;
  std::string		name;
  int			slots;
  int			bits;

  if (server->notConnected(client))
    return;
  ss >> action >> name >> slots >> bits;
  stmt = server->_sql.Statement("insert into services_stream "
				"values(NULL, ?, ?, ?, ?, ?, ?)");
  stmt->Bind(0, client->getId());
  stmt->Bind(1, name);
  stmt->Bind(2, slots);
  stmt->Bind(3, bits);
  stmt->Bind(4, -1);
  stmt->Bind(5, -1);
  stmt->Execute();
  client->setBufWrite(MESG_OK);
  delete stmt;
}

void	Server::actNews(Server* server, Client* client)
{
  SQLiteStatement	*stmt;
  std::stringstream	ss;

  if (server->notConnected(client))
    return;
  client->setBufWrite(MESG_BEGIN);
  stmt = server->_sql.Statement("select subject, date "
				"from news "
				"order by date desc;");
  while (stmt->NextRow())
    {
      ss.str(MESG_EMPTY);
      ss << stmt->ValueString(0) << ' '
	 << stmt->ValueString(1) << std::endl;
      client->setBufWrite(ss.str());
    }
  client->setBufWrite(MESG_END);
  delete stmt;
}

void	Server::actNewsDetail(Server* server, Client* client)
{
  SQLiteStatement	*stmt;
  std::stringstream	ss(client->getBufRead());
  std::string		action;
  int			id;

  if (server->notConnected(client))
    return;
  ss >> action >> id;
  stmt = server->_sql.Statement("select body "
				"from news "
				"order by date desc "
				"limit ?, 1;");
  stmt->Bind(0, id);
  if (stmt->NextRow())
    {
      ss.str(MESG_EMPTY);
      ss << stmt->ValueString(0) << std::endl;
      client->setBufWrite(ss.str());
    }
  else
    client->setBufWrite(MESG_KO);
  delete stmt;
}

std::string	Server::head(void)
{
  std::stringstream	ss;

  ss << "Server: ";
  return (ss.str());
}
