//
// Server.cpp for Server in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Fri Jul 11 21:40:50 2008 caner candan
// Last update Mon Sep 29 19:24:51 2008 caner candan
//

#include <sys/select.h>
#include <cstdlib>
#include <memory>
#include <iostream>
#include <sstream>
#include <string>
#include "Server.h"
#include "Client.h"
#include "SocketServer.h"
#include "SocketClient.h"
#include "State.h"
#include "Apache.h"
#include "IceCast.h"
#include "Signal.h"
#include "Protocole.hpp"
#include "Config.h"

Server::Server()
{
  Config*	config = Config::getInstance();

  _sql.Open(config->getDatabase());

  Signal*	signal = Signal::getInstance();

  signal->addCallback(Signal::INT, this,
		      static_cast<ISignalManager::callback>
		      (&Server::signal));

  _mapAction[Protocole::login] =
    pairCallback(&Server::actLogin, Protocole::empty);
  _mapAction[Protocole::logout] =
    pairCallback(&Server::actLogout, Protocole::ok);
  _mapAction[Protocole::create] =
    pairCallback(&Server::actCreate, Protocole::empty);
  _mapAction[Protocole::status] =
    pairCallback(&Server::actStatus, Protocole::empty);
  _mapAction[Protocole::clients] =
    pairCallback(&Server::actClients, Protocole::empty);
  _mapAction[Protocole::accounts] =
    pairCallback(&Server::actAccounts, Protocole::empty);
  _mapAction[Protocole::message] =
    pairCallback(&Server::actMessage, Protocole::empty);
  _mapAction[Protocole::servicesWeb] =
    pairCallback(&Server::actServicesWeb, Protocole::empty);
  _mapAction[Protocole::servicesStream] =
    pairCallback(&Server::actServicesStream, Protocole::empty);
  _mapAction[Protocole::servicesWebDetail] =
    pairCallback(&Server::actServicesWebDetail, Protocole::empty);
  _mapAction[Protocole::servicesStreamDetail] =
    pairCallback(&Server::actServicesStreamDetail, Protocole::empty);
  _mapAction[Protocole::offerWeb] =
    pairCallback(&Server::actOfferWeb, Protocole::empty);
  _mapAction[Protocole::offerStream] =
    pairCallback(&Server::actOfferStream, Protocole::empty);
  _mapAction[Protocole::createOfferWeb] =
    pairCallback(&Server::actCreateOfferWeb, Protocole::empty);
  _mapAction[Protocole::createOfferStream] =
    pairCallback(&Server::actCreateOfferStream, Protocole::empty);
  _mapAction[Protocole::createWeb] =
    pairCallback(&Server::actCreateWeb, Protocole::empty);
  _mapAction[Protocole::createStream] =
    pairCallback(&Server::actCreateStream, Protocole::empty);
  _mapAction[Protocole::news] =
    pairCallback(&Server::actNews, Protocole::empty);
  _mapAction[Protocole::newsDetail] =
    pairCallback(&Server::actNewsDetail, Protocole::empty);
}

Server::~Server()
{
  destroyListClients();
}

void	Server::signal()
{
  if (Config::getInstance()->isVerbose())
    std::cout << "Server signal" << std::endl;
  destroyListClients();
}

void	Server::destroyListClients()
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

void		Server::addServer(int port)
{
  Client	*client;
  SocketServer	*ss;

  ss = new SocketServer(port);
  client = new Client(ss, Client::SERVER);
  this->_clients.push_back(client);
}

void		Server::addClient(Client *server)
{
  Client	*client;
  SocketClient	*sc;

  sc = new SocketClient(server->getSocket()->getSocket());
  client = new Client(sc, Client::CLIENT);
  this->_clients.push_back(client);
  client->appendBufWrite(Protocole::welcome);
}

void	Server::setFd(fd_set& fdRead, fd_set& fdWrite, int& fdMax)
{
  for (listClients::iterator
	 it = _clients.begin(),
	 end = _clients.end();
       it != end; ++it)
    {
      if (!(*it)->getSocket()->getStatus())
	{
	  delete *it;
	  this->_clients.erase(it);
	  continue;
	}
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

  for (listClients::const_iterator
	 it = _clients.begin(),
	 end = _clients.end();
       it != end; ++it)
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
  Config*	config = Config::getInstance();

  try
    {
      fd_set	fdRead;
      fd_set	fdWrite;
      int	fdMax;
      State*	state = State::getInstance();

      while (state->getState() == State::START)
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
      if (config->isVerbose())
	std::cout << std::endl
		  << "Server stopped." << std::endl;
    }
  catch (bool)
    {
      if (config->isVerbose())
	std::cout << this->head()
		  << "select error" << std::endl;
    }
}

void	Server::serverRead(Client *server)
{
  if (Config::getInstance()->isVerbose())
    std::cout << this->head()
	      << "server read" << std::endl;
  addClient(server);
}

void	Server::clientRead(Client *client)
{
  if (Config::getInstance()->isVerbose())
    std::cout << this->head() << " ["
	      << client->getSocket()->getSocket()
	      << "] client read" << std::endl;
  client->clearBufRead();
  client->appendBufRead(client->getSocket()->recv());
  this->executeAction(client);
}

void	Server::clientWrite(Client *client)
{
  if (Config::getInstance()->isVerbose())
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

  ss >> action;

  if (_mapAction.find(action) == _mapAction.end())
    {
      client->appendBufWrite(Protocole::ko);
      return;
    }

  pairCallback&	pair = _mapAction[action];

  ss.str(Protocole::empty);
  ss << action << ' ';
  client->appendBufWrite(ss.str());
  (this->*pair.first)(client);
  if (!pair.second.empty())
    client->appendBufWrite(pair.second);
}

bool	Server::existLogin(const std::string& login)
{
  std::auto_ptr<SQLiteStatement>	stmt
    (this->_sql.Statement("select 1 "
			  "from users "
			  "where username = ?;"));

  stmt->Bind(0, login);
  return (stmt->NextRow());
}

bool	Server::existLoginPasswd(const std::string& login,
				 const std::string& passwd)
{
  std::auto_ptr<SQLiteStatement>	stmt
    (this->_sql.Statement("select 1 "
			  "from users "
			  "where username = ? "
			  "and password = ?;"));

  stmt->Bind(0, login);
  stmt->Bind(1, passwd);
  return (stmt->NextRow());
}

bool	Server::alreadyConnected(const std::string& login)
{
  for (listClients::const_iterator
	 it = this->getListClients().begin(),
	 end = this->getListClients().end();
       it != end; ++it)
    {
      if ((*it)->isConnected())
	if ((*it)->getLogin() == login)
	  return (true);
    }
  return (false);
}

Client	*Server::findClient(const std::string& login)
{
  for (listClients::const_iterator
	 it = this->getListClients().begin(),
	 end = this->getListClients().end();
       it != end; ++it)
    {
      if ((*it)->isConnected())
	if ((*it)->getLogin() == login)
	  return (*it);
    }
  return (NULL);
}

bool	Server::notConnected(Client *client)
{
  if (!client->isConnected())
    {
      client->appendBufWrite(Protocole::ko);
      return (true);
    }
  return (false);
}

bool	Server::enoughCredit(const int& value, Client* client)
{
  std::auto_ptr<SQLiteStatement>	stmt
    (this->_sql.Statement("select value "
			  "from credit "
			  "where id_user = ?;"));

  stmt->Bind(0, client->getId());
  if (!stmt->NextRow())
    return (false);
  return (stmt->ValueInt(0) >= value);
}

void	Server::addCredit(const int& value, Client* client)
{
  std::auto_ptr<SQLiteStatement>	stmt
    (this->_sql.Statement("update credit "
			  "set value = value + ? "
			  "where id_user = ?;"));
  stmt->Bind(0, value);
  stmt->Bind(1, client->getId());
  stmt->Execute();
  client->setCredit(client->getCredit() + value);
}

void	Server::subCredit(const int& value, Client* client)
{
  std::auto_ptr<SQLiteStatement>	stmt
    (this->_sql.Statement("update credit "
			  "set value = value - ? "
			  "where id_user = ?;"));
  stmt->Bind(0, value);
  stmt->Bind(1, client->getId());
  stmt->Execute();
  client->setCredit(client->getCredit() - value);
}

void	Server::actLogin(Client* client)
{
  std::stringstream	ss(client->getBufRead());
  std::string		action;
  std::string		login;
  std::string		passwd;

  ss >> action >> login >> passwd;
  if (login.empty() || passwd.empty() ||
      !this->existLoginPasswd(login, passwd) ||
      this->alreadyConnected(login))
    {
      client->appendBufWrite(Protocole::ko);
      return;
    }

  std::auto_ptr<SQLiteStatement>	stmt
    (this->_sql.Statement("select users.id, users.username, "
			    "credit.value "
			    "from users, credit "
			    "where users.id = credit.id_user "
			    "and username = ?;"));

  stmt->Bind(0, login);
  if (stmt->NextRow())
    {
      client->setId(stmt->ValueInt(0));
      client->setLogin(stmt->ValueString(1));
      client->setCredit(stmt->ValueInt(2));
    }
  client->appendBufWrite(client->getCredit());
  client->appendBufWrite("\n");
}

void	Server::actLogout(Client* client)
{
  client->setLogin(Protocole::empty);
}

void	Server::actCreate(Client* client)
{
  std::stringstream	ss(client->getBufRead());
  std::string		action;
  std::string		login;
  std::string		passwd;

  ss >> action >> login;
  if (login.empty() || this->existLogin(login))
    {
      client->appendBufWrite(Protocole::ko);
      return;
    }
  passwd = generatePasswd();

  std::auto_ptr<SQLiteStatement>	stmt
    (this->_sql.Statement("insert into users "
			    "values(NULL, ?, ?);"));

  stmt->Bind(0, login);
  stmt->Bind(1, passwd);
  stmt->Execute();
  stmt.reset(this->_sql.Statement("insert into credit "
				    "values(last_insert_rowid(), 0);"));
  stmt->Execute();
  client->appendBufWrite(passwd + '\n');
}

void	Server::actCredit(Client* client)
{
  if (this->notConnected(client))
    return;
  client->appendBufWrite(client->getCredit());
  client->appendBufWrite("\n");
}

void	Server::actStatus(Client* client)
{
  if (!this->notConnected(client))
    client->appendBufWrite(Protocole::ok);
}

void	Server::actClients(Client* client)
{
  if (this->notConnected(client))
    return;

  client->appendBufWrite(Protocole::begin);

  for (listClients::const_iterator
	 it = this->getListClients().begin(),
	 end = this->getListClients().end();
       it != end; ++it)
    {
      if ((*it)->isConnected())
	client->appendBufWrite((*it)->getLogin() + '\n');
    }
  client->appendBufWrite(Protocole::end);
}

void	Server::actAccounts(Client* client)
{
  if (this->notConnected(client))
    return;

  std::auto_ptr<SQLiteStatement>	stmt
    (this->_sql.Statement("select username "
			    "from users "
			    "order by username;"));
  std::stringstream	ss;

  client->appendBufWrite(Protocole::begin);
  while (stmt->NextRow())
    {
      ss.str(Protocole::empty);
      ss << stmt->ValueString(0) << std::endl;
      client->appendBufWrite(ss.str());
    }
  client->appendBufWrite(Protocole::end);
}

void	Server::actMessage(Client* client)
{
  if (this->notConnected(client))
    return;

  std::string	str(client->getBufRead());
  std::string	action;
  std::string	login;
  std::string	message;
  size_t	separator;
  Client	*to;

  separator = str.find(' ');
  action = str.substr(0, separator);
  str = str.substr(separator + 1);
  separator = str.find(' ');
  login = str.substr(0, separator);
  message = str.substr(separator + 1);
  if (login.empty() || message.empty() ||
      !(to = this->findClient(login)))
    {
      client->appendBufWrite(Protocole::ko);
      return;
    }
  to->appendBufWrite(std::string(Protocole::message) + ' ');
  to->appendBufWrite(client->getLogin() + ' ' + message);
  client->appendBufWrite(Protocole::ok);
}

void	Server::actServicesWeb(Client* client)
{
  if (this->notConnected(client))
    return;

  std::auto_ptr<SQLiteStatement>	stmt
    (this->_sql.Statement("select name "
			    "from services_web "
			    "where id_user = ? "
			    "order by name;"));
  std::stringstream	ss;

  client->appendBufWrite(Protocole::begin);
  stmt->Bind(0, client->getId());
  while (stmt->NextRow())
    {
      ss.str(Protocole::empty);
      ss << stmt->ValueString(0) << std::endl;
      client->appendBufWrite(ss.str());
    }
  client->appendBufWrite(Protocole::end);
}

void	Server::actServicesStream(Client* client)
{
  if (this->notConnected(client))
    return;

  std::auto_ptr<SQLiteStatement>	stmt
    (this->_sql.Statement("select name "
			    "from services_stream "
			    "where id_user = ? "
			    "order by name;"));
  std::stringstream	ss;

  client->appendBufWrite(Protocole::begin);
  stmt->Bind(0, client->getId());
  while (stmt->NextRow())
    {
      ss.str(Protocole::empty);
      ss << stmt->ValueString(0) << std::endl;
      client->appendBufWrite(ss.str());
    }
  client->appendBufWrite(Protocole::end);
}

void	Server::actServicesWebDetail(Client* client)
{
  if (this->notConnected(client))
    return;

  std::auto_ptr<SQLiteStatement>	stmt
    (this->_sql.Statement("select name, space, nb_db, "
			    "domain, created, expired "
			    "from services_web "
			    "where id_user = ? "
			    "order by name "
			    "limit ?, 1;"));
  std::stringstream	ss(client->getBufRead());
  std::string		action;
  int			row;

  row = 0;
  ss >> action >> row;
  stmt->Bind(0, client->getId());
  stmt->Bind(1, row);
  if (stmt->NextRow())
    {
      ss.str(Protocole::empty);
      ss << stmt->ValueString(0)
	 << ' ' << stmt->ValueString(1)
	 << ' ' << stmt->ValueString(2)
	 << ' ' << stmt->ValueString(3)
	 << ' ' << stmt->ValueString(4)
	 << ' ' << stmt->ValueString(5)
	 << std::endl;
      client->appendBufWrite(ss.str());
    }
  else
    client->appendBufWrite(Protocole::ko);
}

void	Server::actServicesStreamDetail(Client* client)
{
  if (this->notConnected(client))
    return;

  std::auto_ptr<SQLiteStatement>	stmt
    (this->_sql.Statement("select name, slots, bits, "
			    "title, created, expired "
			    "from services_stream "
			    "where id_user = ? "
			    "order by name "
			    "limit ?, 1;"));
  std::stringstream	ss(client->getBufRead());
  std::string		action;
  int			row;

  row = 0;
  ss >> action >> row;
  stmt->Bind(0, client->getId());
  stmt->Bind(1, row);
  if (stmt->NextRow())
    {
      ss.str(Protocole::empty);
      ss << stmt->ValueString(0)
	 << ' ' << stmt->ValueString(1)
	 << ' ' << stmt->ValueString(2)
	 << ' ' << stmt->ValueString(3)
	 << ' ' << stmt->ValueString(4)
	 << ' ' << stmt->ValueString(5)
	 << std::endl;
      client->appendBufWrite(ss.str());
    }
  else
    client->appendBufWrite(Protocole::ko);
}

void	Server::actOfferWeb(Client* client)
{
  if (this->notConnected(client))
    return;

  std::auto_ptr<SQLiteStatement>	stmt
    (this->_sql.Statement("select price, name "
			    "from offer_web "
			    "order by name;"));
  std::stringstream	ss;

  client->appendBufWrite(Protocole::begin);
  while (stmt->NextRow())
    {
      ss.str(Protocole::empty);
      ss << stmt->ValueString(0)
	 << ' ' << stmt->ValueString(1)
	 << std::endl;
      client->appendBufWrite(ss.str());
    }
  client->appendBufWrite(Protocole::end);
}

void	Server::actOfferStream(Client* client)
{
  if (this->notConnected(client))
    return;

  std::auto_ptr<SQLiteStatement>	stmt
    (this->_sql.Statement("select price, name "
			    "from offer_stream "
			    "order by name;"));
  std::stringstream	ss;

  client->appendBufWrite(Protocole::begin);
  while (stmt->NextRow())
    {
      ss.str(Protocole::empty);
      ss << stmt->ValueString(0)
	 << ' ' << stmt->ValueString(1)
	 << std::endl;
      client->appendBufWrite(ss.str());
    }
  client->appendBufWrite(Protocole::end);
}

void	Server::actCreateOfferWeb(Client* client)
{
  if (this->notConnected(client))
    return;

  std::stringstream	ss(client->getBufRead());
  std::string		action;
  std::string		name;
  int			row;
  std::string		domain;
  int			price;
  int			space;
  int			nbDb;

  row = 0;
  ss >> action >> name >> row >> domain;

  std::auto_ptr<SQLiteStatement>	stmt
    (this->_sql.Statement("select price, space, nb_db "
			    "from offer_web "
			    "order by name "
			    "limit ?, 1;"));

  stmt->Bind(0, row);
  if (!stmt->NextRow())
    {
      client->appendBufWrite(Protocole::ko);
      return;

    }
  price = stmt->ValueInt(0);
  if (!this->enoughCredit(price, client))
    {
      client->appendBufWrite(Protocole::ko);
      return;
    }
  space = stmt->ValueInt(1);
  nbDb = stmt->ValueInt(2);
  stmt.reset(this->_sql.Statement("insert into services_web "
				    "values(NULL, ?, ?, ?, ?, ?, ?, ?);"));
  stmt->Bind(0, client->getId());
  stmt->Bind(1, name);
  stmt->Bind(2, space);
  stmt->Bind(3, nbDb);
  stmt->Bind(4, domain);
  stmt->Bind(5, 1);
  stmt->Bind(6, 1);
  stmt->Execute();
  this->subCredit(price, client);

  std::auto_ptr<IServerWeb>	serverWeb(new Apache(client));

  serverWeb->createHost(domain);
  client->appendBufWrite(Protocole::ok);
}

void	Server::actCreateOfferStream(Client* client)
{
  if (this->notConnected(client))
    return;

  std::stringstream		ss(client->getBufRead());
  std::string			action;
  std::string			name;
  int				row;
  std::string			title;
  int				price;
  int				slots;
  int				bits;

  row = 0;
  ss >> action >> name >> row >> title;

  std::auto_ptr<SQLiteStatement>	stmt
    (this->_sql.Statement("select price, slots, bits "
			    "from offer_stream "
			    "order by name "
			    "limit ?, 1;"));

  stmt->Bind(0, row);
  if (!stmt->NextRow())
    {
      client->appendBufWrite(Protocole::ko);
      return;
    }
  price = stmt->ValueInt(0);
  if (!this->enoughCredit(price, client))
    {
      client->appendBufWrite(Protocole::ko);
      return;
    }
  slots = stmt->ValueInt(1);
  bits = stmt->ValueInt(2);
  stmt.reset(this->_sql.Statement("insert into services_stream "
				    "values(NULL, ?, ?, ?, ?, ?, ?, ?);"));
  stmt->Bind(0, client->getId());
  stmt->Bind(1, name);
  stmt->Bind(2, slots);
  stmt->Bind(3, bits);
  stmt->Bind(4, title);
  stmt->Bind(5, 1);
  stmt->Bind(6, 1);
  stmt->Execute();
  this->subCredit(price, client);

  std::auto_ptr<IServerStream>	serverStream(new IceCast(client));

  serverStream->createStream(name, slots, bits);
  client->appendBufWrite(Protocole::ok);
}

void	Server::actCreateWeb(Client* client)
{
  if (this->notConnected(client))
    return;

  std::stringstream	ss(client->getBufRead());
  std::string		action;
  std::string		name;
  int			space;
  int			nbDb;
  int			price;
  std::string		domain;

  space = 0;
  nbDb = 0;
  ss >> action >> name >> space >> nbDb >> domain;
  if (name.empty() || !space || !nbDb || domain.empty())
    {
      client->appendBufWrite(Protocole::ko);
      return;
    }
  price = ((space / Protocole::ratioWebSpace)
	   + (nbDb / Protocole::ratioWebDb));
  if (!this->enoughCredit(price, client))
    {
      client->appendBufWrite(Protocole::ko);
      return;
    }

  std::auto_ptr<SQLiteStatement>	stmt
    (this->_sql.Statement("insert into services_web "
			  "values(NULL, ?, ?, ?, ?, ?, ?, ?);"));

  stmt->Bind(0, client->getId());
  stmt->Bind(1, name);
  stmt->Bind(2, space);
  stmt->Bind(3, nbDb);
  stmt->Bind(4, domain);
  stmt->Bind(5, 1);
  stmt->Bind(6, 1);
  stmt->Execute();
  this->subCredit(price, client);

  std::auto_ptr<IServerWeb>	serverWeb(new Apache(client));

  serverWeb->createHost(domain);
  client->appendBufWrite(Protocole::ok);
}

void	Server::actCreateStream(Client* client)
{
  if (this->notConnected(client))
    return;

  std::stringstream	ss(client->getBufRead());
  std::string		action;
  std::string		name;
  int			slots;
  int			bits;
  int			price;
  std::string		title;

  ss >> action >> name >> slots >> bits >> title;
  if (name.empty() || !slots || !bits || title.empty())
    {
      client->appendBufWrite(Protocole::ko);
      return;
    }
  price = ((slots / Protocole::ratioStreamSlot)
	   + (bits / Protocole::ratioStreamBits));
  if (!this->enoughCredit(price, client))
    {
      client->appendBufWrite(Protocole::ko);
      return;
    }

  std::auto_ptr<SQLiteStatement>	stmt
    (this->_sql.Statement("insert into services_stream "
			    "values(NULL, ?, ?, ?, ?, ?, ?, ?);"));

  stmt->Bind(0, client->getId());
  stmt->Bind(1, name);
  stmt->Bind(2, slots);
  stmt->Bind(3, bits);
  stmt->Bind(4, title);
  stmt->Bind(5, 1);
  stmt->Bind(6, 1);
  stmt->Execute();
  this->subCredit(price, client);

  std::auto_ptr<IServerStream>	serverStream(new IceCast(client));

  serverStream->createStream(name, slots, bits);
  client->appendBufWrite(Protocole::ok);
}

void	Server::actNews(Client* client)
{
  if (this->notConnected(client))
    return;

  std::auto_ptr<SQLiteStatement>	stmt
    (this->_sql.Statement("select date, subject "
			    "from news "
			    "order by date desc;"));
  std::stringstream	ss;

  client->appendBufWrite(Protocole::begin);
  while (stmt->NextRow())
    {
      ss.str(Protocole::empty);
      ss << stmt->ValueString(0) << ' '
	 << stmt->ValueString(1) << std::endl;
      client->appendBufWrite(ss.str());
    }
  client->appendBufWrite(Protocole::end);
}

void	Server::actNewsDetail(Client* client)
{
  if (this->notConnected(client))
    return;

  std::auto_ptr<SQLiteStatement>	stmt
    (this->_sql.Statement("select body "
			    "from news "
			    "order by date desc "
			    "limit ?, 1;"));
  std::stringstream	ss(client->getBufRead());
  std::string		action;
  int			id;

  ss >> action >> id;
  stmt->Bind(0, id);
  if (stmt->NextRow())
    {
      ss.str(Protocole::empty);
      ss << stmt->ValueString(0) << std::endl;
      client->appendBufWrite(ss.str());
    }
  else
    client->appendBufWrite(Protocole::ko);
}

std::string	Server::generatePasswd()
{
  const size_t&	size = std::string(Protocole::passwdCharacters).size();
  std::string	res;

  srand((unsigned int)time(0));
  for (int i = 0; i < Protocole::passwdSize; i++)
    res += Protocole::passwdCharacters[rand() % size];
  return (res);
}

std::string	Server::head(void)
{
  std::stringstream	ss;

  ss << "Server: ";
  return (ss.str());
}
