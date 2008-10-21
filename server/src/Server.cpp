//
// Server.cpp for Server in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Fri Jul 11 21:40:50 2008 caner candan
// Last update Mon Oct 13 19:32:35 2008 caner candan
//

#include <sys/select.h>
#include <signal.h>
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
#include "Protocole.h"
#include "Config.h"

Server::Server()
{
  Config*	config = Config::getInstance();

  _sql.Open(config->getDatabase());

  Signal*	signal = Signal::getInstance();

  signal->addCallback(Signal::INT, this,
		      static_cast<ISignalManager::callback>
		      (&Server::signal));

  _mapAction[LOGIN] = pairCallback(&Server::actLogin, EMPTY);
  _mapAction[LOGOUT] = pairCallback(&Server::actLogout, OK);
  _mapAction[CREATE] = pairCallback(&Server::actCreate, EMPTY);

  _mapAction[STATUS] = pairCallback(&Server::actStatus, EMPTY);
  _mapAction[CLIENTS] = pairCallback(&Server::actClients, EMPTY);
  _mapAction[ACCOUNTS] = pairCallback(&Server::actAccounts, EMPTY);
  _mapAction[MESSAGE] = pairCallback(&Server::actMessage, EMPTY);

  _mapAction[SERVICES_WEB] = pairCallback(&Server::actServicesWeb, EMPTY);
  _mapAction[SERVICES_STREAM] =
    pairCallback(&Server::actServicesStream, EMPTY);
  _mapAction[SERVICES_WEB_DETAIL] =
    pairCallback(&Server::actServicesWebDetail, EMPTY);
  _mapAction[SERVICES_STREAM_DETAIL] =
    pairCallback(&Server::actServicesStreamDetail, EMPTY);

  _mapAction[OFFER_WEB] = pairCallback(&Server::actOfferWeb, EMPTY);
  _mapAction[OFFER_STREAM] = pairCallback(&Server::actOfferStream, EMPTY);

  _mapAction[CREATE_OFFER_WEB] =
    pairCallback(&Server::actCreateOfferWeb, EMPTY);
  _mapAction[CREATE_OFFER_STREAM] =
    pairCallback(&Server::actCreateOfferStream, EMPTY);

  _mapAction[CREATE_WEB] = pairCallback(&Server::actCreateWeb, EMPTY);
  _mapAction[CREATE_STREAM] = pairCallback(&Server::actCreateStream, EMPTY);

  _mapAction[NEWS] = pairCallback(&Server::actNews, EMPTY);
  _mapAction[NEWS_DETAIL] = pairCallback(&Server::actNewsDetail, EMPTY);

  _mapAction[STREAM_STATUS] = pairCallback(&Server::actStreamStatus, EMPTY);
  _mapAction[STREAM_START] = pairCallback(&Server::actStreamStart, EMPTY);
  _mapAction[STREAM_STOP] = pairCallback(&Server::actStreamStop, EMPTY);
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
  SocketServer*	ss = new SocketServer(port);
  Client*	client = new Client(ss, Client::SERVER);

  this->_clients.push_back(client);
}

void		Server::addClient(Client *server)
{
  SocketClient*	sc = new SocketClient(server->getSocket()->getSocket());
  Client*	client = new Client(sc, Client::CLIENT);

  this->_clients.push_back(client);

  client->appendBufWrite(WELCOME);
  client->appendBufWrite(NL);
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
      client->appendBufWrite(KO);
      client->appendBufWrite(NL);
      return;
    }

  pairCallback&	pair = _mapAction[action];

  client->appendBufWrite(action);
  client->appendBufWrite(" ");

  (this->*pair.first)(client);
  if (!pair.second.empty())
    {
      client->appendBufWrite(pair.second);
      client->appendBufWrite(NL);
    }
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
      client->appendBufWrite(KO);
      client->appendBufWrite(NL);
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
      client->appendBufWrite(KO);
      client->appendBufWrite(NL);
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
  client->appendBufWrite(NL);
}

void	Server::actLogout(Client* client)
{
  client->setLogin(EMPTY);
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
      client->appendBufWrite(KO);
      client->appendBufWrite(NL);
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
  client->appendBufWrite(NL);
}

void	Server::actStatus(Client* client)
{
  if (!this->notConnected(client))
    {
      client->appendBufWrite(KO);
      client->appendBufWrite(NL);
    }
}

void	Server::actClients(Client* client)
{
  if (this->notConnected(client))
    return;

  client->appendBufWrite(BEGIN);
  client->appendBufWrite(NL);

  for (listClients::const_iterator
	 it = this->getListClients().begin(),
	 end = this->getListClients().end();
       it != end; ++it)
    {
      if ((*it)->isConnected())
	{
	  client->appendBufWrite((*it)->getLogin());
	  client->appendBufWrite(NL);
	}
    }

  client->appendBufWrite(END);
  client->appendBufWrite(NL);
}

void	Server::actAccounts(Client* client)
{
  if (this->notConnected(client))
    return;

  std::auto_ptr<SQLiteStatement>	stmt
    (this->_sql.Statement("select username "
			  "from users "
			  "order by username;"));

  client->appendBufWrite(BEGIN);
  client->appendBufWrite(NL);

  while (stmt->NextRow())
    {
      client->appendBufWrite(stmt->ValueString(0));
      client->appendBufWrite(NL);
    }

  client->appendBufWrite(END);
  client->appendBufWrite(NL);
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
  Client*	to;

  separator = str.find(' ');
  action = str.substr(0, separator);
  str = str.substr(separator + 1);
  separator = str.find(' ');
  login = str.substr(0, separator);
  message = str.substr(separator + 1);

  if (login.empty() || message.empty() ||
      !(to = this->findClient(login)))
    {
      client->appendBufWrite(KO);
      client->appendBufWrite(NL);
      return;
    }

  to->appendBufWrite(MESSAGE);
  to->appendBufWrite(" ");
  to->appendBufWrite(client->getLogin());
  to->appendBufWrite(" ");
  to->appendBufWrite(message);
  to->appendBufWrite(NL);

  client->appendBufWrite(OK);
  client->appendBufWrite(NL);
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

  client->appendBufWrite(BEGIN);
  client->appendBufWrite(NL);

  stmt->Bind(0, client->getId());

  while (stmt->NextRow())
    {
      client->appendBufWrite(stmt->ValueString(0));
      client->appendBufWrite(NL);
    }

  client->appendBufWrite(END);
  client->appendBufWrite(NL);
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

  client->appendBufWrite(BEGIN);
  client->appendBufWrite(NL);

  stmt->Bind(0, client->getId());
  while (stmt->NextRow())
    {
      client->appendBufWrite(stmt->ValueString(0));
      client->appendBufWrite(NL);
    }

  client->appendBufWrite(END);
  client->appendBufWrite(NL);
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
  int			row = 0;

  ss >> action >> row;
  stmt->Bind(0, client->getId());
  stmt->Bind(1, row);

  if (stmt->NextRow())
    {
      std::stringstream	ss;

      ss << stmt->ValueString(0)
	 << ' ' << stmt->ValueString(1)
	 << ' ' << stmt->ValueString(2)
	 << ' ' << stmt->ValueString(3)
	 << ' ' << stmt->ValueString(4)
	 << ' ' << stmt->ValueString(5);
      client->appendBufWrite(ss.str());
      client->appendBufWrite(NL);
    }
  else
    {
      client->appendBufWrite(KO);
      client->appendBufWrite(NL);
    }
}

void	Server::actServicesStreamDetail(Client* client)
{
  if (this->notConnected(client))
    return;

  std::auto_ptr<SQLiteStatement>	stmt
    (this->_sql.Statement("select name, slots, bits, "
			  "title, port, created, expired "
			  "from services_stream "
			  "where id_user = ? "
			  "order by name "
			  "limit ?, 1;"));
  std::stringstream	ss(client->getBufRead());
  std::string		action;
  int			row = 0;

  ss >> action >> row;
  stmt->Bind(0, client->getId());
  stmt->Bind(1, row);
  if (stmt->NextRow())
    {
      std::stringstream	ss;

      ss << stmt->ValueString(0)
	 << ' ' << stmt->ValueString(1)
	 << ' ' << stmt->ValueString(2)
	 << ' ' << stmt->ValueString(3)
	 << ' ' << stmt->ValueString(4)
	 << ' ' << (_streamOnline(client, stmt->ValueString(0)) ? '1' : '0')
	 << ' ' << stmt->ValueString(5)
	 << ' ' << stmt->ValueString(6);
      client->appendBufWrite(ss.str());
      client->appendBufWrite(NL);
    }
  else
    {
      client->appendBufWrite(KO);
      client->appendBufWrite(NL);
    }
}

void	Server::actOfferWeb(Client* client)
{
  if (this->notConnected(client))
    return;

  std::auto_ptr<SQLiteStatement>	stmt
    (this->_sql.Statement("select price, name "
			  "from offer_web "
			  "order by name;"));

  client->appendBufWrite(BEGIN);
  client->appendBufWrite(NL);

  while (stmt->NextRow())
    {
      client->appendBufWrite(stmt->ValueString(0));
      client->appendBufWrite(SP);
      client->appendBufWrite(stmt->ValueString(1));
      client->appendBufWrite(NL);
    }

  client->appendBufWrite(END);
  client->appendBufWrite(NL);
}

void	Server::actOfferStream(Client* client)
{
  if (this->notConnected(client))
    return;

  std::auto_ptr<SQLiteStatement>	stmt
    (this->_sql.Statement("select price, name "
			  "from offer_stream "
			  "order by name;"));

  client->appendBufWrite(BEGIN);
  client->appendBufWrite(NL);

  while (stmt->NextRow())
    {
      client->appendBufWrite(stmt->ValueString(0));
      client->appendBufWrite(SP);
      client->appendBufWrite(stmt->ValueString(1));
      client->appendBufWrite(NL);
    }

  client->appendBufWrite(END);
  client->appendBufWrite(NL);
}

void	Server::actCreateOfferWeb(Client* client)
{
  if (this->notConnected(client))
    return;

  std::stringstream	ss(client->getBufRead());
  std::string		action;
  std::string		name;
  int			row = 0;
  std::string		domain;

  ss >> action >> name >> row >> domain;

  std::auto_ptr<SQLiteStatement>	stmt
    (this->_sql.Statement("select price, space, nb_db "
			  "from offer_web "
			  "order by name "
			  "limit ?, 1;"));

  stmt->Bind(0, row);
  if (!stmt->NextRow())
    {
      client->appendBufWrite(KO);
      client->appendBufWrite(NL);
      return;
    }

  int	price = stmt->ValueInt(0);

  if (!this->enoughCredit(price, client))
    {
      client->appendBufWrite(KO);
      client->appendBufWrite(NL);
      return;
    }

  int	space = stmt->ValueInt(1);
  int	nbDb = stmt->ValueInt(2);

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
  client->appendBufWrite(OK);
  client->appendBufWrite(NL);
}

void	Server::actCreateOfferStream(Client* client)
{
  if (this->notConnected(client))
    return;

  std::stringstream	ss(client->getBufRead());
  std::string		action;
  std::string		name;
  int			row = 0;
  std::string		title;

  ss >> action >> name >> row >> title;

  std::auto_ptr<SQLiteStatement>	stmt
    (this->_sql.Statement("select price, slots, bits "
			  "from offer_stream "
			  "order by name "
			  "limit ?, 1;"));

  stmt->Bind(0, row);
  if (!stmt->NextRow())
    {
      client->appendBufWrite(KO);
      client->appendBufWrite(NL);
      return;
    }

  int	price = stmt->ValueInt(0);

  if (!this->enoughCredit(price, client))
    {
      client->appendBufWrite(KO);
      client->appendBufWrite(NL);
      return;
    }

  Stream	stream;

  stream.setLogin(client->getLogin());
  stream.setName(name);
  stream.setSlots(stmt->ValueInt(1));
  stream.setBits(stmt->ValueInt(2));
  stream.setTitle(title);

  stmt.reset(this->_sql.Statement("select max(port) + 2 "
				  "from services_stream;"));

  if (!stmt->NextRow())
    stream.setPort(9000);
  else
    stream.setPort(stmt->ValueInt(0));

  stmt.reset(this->_sql.Statement("insert into services_stream "
				  "values(NULL, ?, ?, ?, ?, ?, ?, ?, ?, ?);"));

  stmt->Bind(0, client->getId());
  stmt->Bind(1, stream.getName());
  stmt->Bind(2, stream.getSlots());
  stmt->Bind(3, stream.getBits());
  stmt->Bind(4, stream.getTitle());
  stmt->Bind(5, stream.getPort());
  stmt->Bind(6, 0);
  stmt->Bind(7, 1);
  stmt->Bind(8, 1);
  stmt->Execute();

  this->subCredit(price, client);

  IceCast	serverStream(stream);

  serverStream.createStream();

  client->appendBufWrite(OK);
  client->appendBufWrite(NL);
}

void	Server::actCreateWeb(Client* client)
{
  if (this->notConnected(client))
    return;

  std::stringstream	ss(client->getBufRead());
  std::string		action;
  std::string		name;
  int			space = 0;
  int			nbDb = 0;
  std::string		domain;

  ss >> action >> name >> space >> nbDb >> domain;
  if (name.empty() || !space || !nbDb || domain.empty())
    {
      client->appendBufWrite(KO);
      client->appendBufWrite(NL);
      return;
    }

  int	price = ((space / RATIO_WEB_SPACE)
		 + (nbDb / RATIO_WEB_DB));

  if (!this->enoughCredit(price, client))
    {
      client->appendBufWrite(KO);
      client->appendBufWrite(NL);
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

  client->appendBufWrite(OK);
  client->appendBufWrite(NL);
}

void	Server::actCreateStream(Client* client)
{
  if (this->notConnected(client))
    return;

  std::stringstream	ss(client->getBufRead());
  std::string		action;
  std::string		name;
  int			slots = 0;
  int			bits = 0;
  std::string		title;

  ss >> action >> name >> slots >> bits >> title;

  if (name.empty() || !slots || !bits || title.empty())
    {
      client->appendBufWrite(KO);
      client->appendBufWrite(NL);
      return;
    }

  int	price = ((slots / RATIO_STREAM_SLOT)
		 + (bits / RATIO_STREAM_BITS));

  if (!this->enoughCredit(price, client))
    {
      client->appendBufWrite(KO);
      client->appendBufWrite(NL);
      return;
    }

  Stream	stream;

  stream.setLogin(client->getLogin());
  stream.setName(name);
  stream.setSlots(slots);
  stream.setBits(bits);
  stream.setTitle(title);

  std::auto_ptr<SQLiteStatement>	stmt
    (this->_sql.Statement("select max(port) + 2 "
			  "from services_stream;"));

  if (!stmt->NextRow())
    stream.setPort(9000);
  else
    stream.setPort(stmt->ValueInt(0));

  stmt.reset(this->_sql.Statement("insert into services_stream "
				  "values(NULL, ?, ?, ?, ?, ?, ?, ?, ?, ?);"));

  stmt->Bind(0, client->getId());
  stmt->Bind(1, stream.getName());
  stmt->Bind(2, stream.getSlots());
  stmt->Bind(3, stream.getBits());
  stmt->Bind(4, stream.getTitle());
  stmt->Bind(5, stream.getPort());
  stmt->Bind(6, 0);
  stmt->Bind(6, 1);
  stmt->Bind(7, 1);
  stmt->Execute();

  this->subCredit(price, client);

  IceCast	serverStream(stream);

  serverStream.createStream();

  client->appendBufWrite(OK);
  client->appendBufWrite(NL);
}

void	Server::actNews(Client* client)
{
  if (this->notConnected(client))
    return;

  std::auto_ptr<SQLiteStatement>	stmt
    (this->_sql.Statement("select date, subject "
			  "from news "
			  "order by date desc;"));

  client->appendBufWrite(BEGIN);
  client->appendBufWrite(NL);

  while (stmt->NextRow())
    {
      client->appendBufWrite(stmt->ValueString(0));
      client->appendBufWrite(SP);
      client->appendBufWrite(stmt->ValueString(1));
      client->appendBufWrite(NL);
    }

  client->appendBufWrite(END);
  client->appendBufWrite(NL);
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
  int			id = 0;

  ss >> action >> id;
  stmt->Bind(0, id);

  if (stmt->NextRow())
    {
      client->appendBufWrite(stmt->ValueString(0));
      client->appendBufWrite(NL);
      return;
    }

  client->appendBufWrite(KO);
  client->appendBufWrite(NL);
}

void	Server::actStreamStatus(Client* client)
{
  if (this->notConnected(client))
    return;

  std::stringstream	ss(client->getBufRead());
  std::string		action;
  std::string		name;

  ss >> action >> name;

  if (_streamOnline(client, name))
    {
      client->appendBufWrite(OK);
      client->appendBufWrite(NL);

      return;
    }

  client->appendBufWrite(KO);
  client->appendBufWrite(NL);
}

void	Server::actStreamStart(Client* client)
{
  if (this->notConnected(client))
    return;

  std::stringstream	ss(client->getBufRead());
  std::string		action;
  std::string		name;

  ss >> action >> name;

  if (_streamOnline(client, name))
    {
      client->appendBufWrite(KO);
      client->appendBufWrite(NL);

      return;
    }

  if (!(_mapStreamPid[name][client->getLogin()] = ::fork()))
    {
      std::cout << "debug: [" << "I'm the son" << ']' << std::endl;

      std::stringstream	ss;

      ss << "icecast/" << client->getLogin()
	 << "/" << name << "/icecast.xml";

//       ::execl("/usr/local/bin/icecast", "icecast",
// 	      "-c", ss.str().c_str(), (char*)0);

      ::execl("/usr/bin/yes", "yes", (char*)0);

      std::cerr << "execl error" << std::endl;
      ::exit(-1);
    }
  std::cout << "debug: [" << "I'm the father"
	    << std::endl << "pid child: "
	    << _mapStreamPid[name][client->getLogin()] << ']' << std::endl;

  client->appendBufWrite(OK);
  client->appendBufWrite(NL);
}

void	Server::actStreamStop(Client* client)
{
  if (this->notConnected(client))
    return;

  std::stringstream	ss(client->getBufRead());
  std::string		action;
  std::string		name;

  ss >> action >> name;

  if (_streamOnline(client, name))
    {
      pid_t&	pid = _mapStreamPid[name][client->getLogin()];

      ::kill(pid, SIGQUIT);

      pid = 0;

      client->appendBufWrite(OK);
      client->appendBufWrite(NL);

      return;
    }

  client->appendBufWrite(KO);
  client->appendBufWrite(NL);
}

std::string	Server::generatePasswd()
{
  const size_t	size = std::string(PASSWD_CHARACTERS).size();
  std::string	res;

  srand((unsigned int)time(0));
  for (int i = 0; i < PASSWD_SIZE; i++)
    res += PASSWD_CHARACTERS[rand() % size];
  return (res);
}

bool	Server::_streamOnline(Client* client, const std::string& name)
{
  if (_mapStreamPid.find(name) != _mapStreamPid.end())
    {
      mapClientPid&	map = _mapStreamPid[name];

      if (map.find(client->getLogin()) != map.end())
	{
	  pid_t&	pid = map[client->getLogin()];

	  if (pid)
	    return (true);
	}
    }
  return (false);
}

std::string	Server::head(void)
{
  return ("Server: ");
}
