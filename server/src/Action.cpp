//
// Action.cpp for server in /home/candan_c/cu/rendu/qlik/server/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Oct 26 17:42:49 2008 caner candan
// Last update Thu Oct 30 14:45:46 2008 caner candan
//

#include <signal.h>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include "Action.h"
#include "Protocole.h"
#include "Database.h"
#include "Credit.h"
#include "Apache.h"
#include "IceCast.h"

Action::Action(Server* server, Client* client)
  : _server(server), _client(client)
{
  _fillMapAction();
}

Action::~Action()
{}

void	Action::execute()
{
  std::stringstream	ss(_client->getBufRead());
  std::string		action;

  ss >> action;

  if (_mapAction.find(action) == _mapAction.end())
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);
      return;
    }

  pairCallback&	pair = _mapAction[action];

  _client->appendBufWrite(action);
  _client->appendBufWrite(" ");

  (this->*pair.first)();
  if (!pair.second.empty())
    {
      _client->appendBufWrite(pair.second);
      _client->appendBufWrite(NL);
    }
}

void	Action::_fillMapAction()
{
  _mapAction[LOGIN] = pairCallback(&Action::_actLogin, EMPTY);
  _mapAction[LOGOUT] = pairCallback(&Action::_actLogout, OK);
  _mapAction[CREATE] = pairCallback(&Action::_actCreate, EMPTY);

  _mapAction[CREDIT] = pairCallback(&Action::_actCredit, EMPTY);

  _mapAction[STATUS] = pairCallback(&Action::_actStatus, EMPTY);

  _mapAction[CLIENTS] = pairCallback(&Action::_actClients, EMPTY);
  _mapAction[ACCOUNTS] = pairCallback(&Action::_actAccounts, EMPTY);
  _mapAction[MESSAGE] = pairCallback(&Action::_actMessage, EMPTY);

  _mapAction[WEB] = pairCallback(&Action::_actWeb, EMPTY);
  _mapAction[STREAM] =
    pairCallback(&Action::_actStream, EMPTY);

  _mapAction[WEB_DETAIL] =
    pairCallback(&Action::_actWebDetail, EMPTY);
  _mapAction[STREAM_DETAIL] =
    pairCallback(&Action::_actStreamDetail, EMPTY);

  _mapAction[OFFER_WEB] = pairCallback(&Action::_actOfferWeb, EMPTY);
  _mapAction[OFFER_STREAM] = pairCallback(&Action::_actOfferStream, EMPTY);

  _mapAction[CREATE_OFFER_WEB] =
    pairCallback(&Action::_actCreateOfferWeb, EMPTY);
  _mapAction[CREATE_OFFER_STREAM] =
    pairCallback(&Action::_actCreateOfferStream, EMPTY);

  _mapAction[CREATE_WEB] = pairCallback(&Action::_actCreateWeb, EMPTY);
  _mapAction[CREATE_STREAM] = pairCallback(&Action::_actCreateStream, EMPTY);

  _mapAction[NEWS] = pairCallback(&Action::_actNews, EMPTY);
  _mapAction[NEWS_DETAIL] = pairCallback(&Action::_actNewsDetail, EMPTY);

  _mapAction[STREAM_STATUS] = pairCallback(&Action::_actStreamStatus, EMPTY);
  _mapAction[STREAM_START] = pairCallback(&Action::_actStreamStart, EMPTY);
  _mapAction[STREAM_STOP] = pairCallback(&Action::_actStreamStop, EMPTY);

  _mapAction[HALT] = pairCallback(&Action::_actHalt, EMPTY);
  _mapAction[BREAK] = pairCallback(&Action::_actBreak, EMPTY);
  _mapAction[PLAY] = pairCallback(&Action::_actPlay, EMPTY);
  _mapAction[RELOAD] = pairCallback(&Action::_actReload, EMPTY);
}

void	Action::_actLogin()
{
  std::stringstream	ss(_client->getBufRead());
  std::string		action;
  std::string		login;
  std::string		passwd;

  ss >> action >> login >> passwd;

  if (login.empty() || passwd.empty() ||
      !_existLoginPasswd(login, passwd) ||
      _alreadyConnected(login))
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);

      return;
    }

  Database*		database = Database::getInstance();
  SQLiteStatement*	stmt =
    database->database().Statement("select users.id, users.username, "
				   "credit.value "
				   "from users, credit "
				   "where users.id = credit.id_user "
				   "and username = ?;");

  stmt->Bind(0, login);

  if (stmt->NextRow())
    {
      _client->setId(stmt->ValueInt(0));
      _client->setLogin(stmt->ValueString(1));
      _client->setCredit(stmt->ValueInt(2));
    }

  stmt->End();

  _client->appendBufWrite(_client->getCredit());
  _client->appendBufWrite(NL);
}

void	Action::_actLogout()
{
  _client->setLogin(EMPTY);
}

void	Action::_actCreate()
{
  std::stringstream	ss(_client->getBufRead());
  std::string		action;
  std::string		login;
  std::string		passwd;

  ss >> action >> login;
  if (login.empty() || _existLogin(login))
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);
      return;
    }
  passwd = _generatePasswd();

  Database*		database = Database::getInstance();
  SQLiteStatement*	stmt =
    database->database().Statement("insert into users "
				   "values(NULL, ?, ?);");

  stmt->Bind(0, login);
  stmt->Bind(1, passwd);

  stmt->Execute();

  stmt = database->database().Statement("insert into credit "
					"values(last_insert_rowid(), 0);");
  stmt->Execute();

  _client->appendBufWrite(passwd + '\n');
}

void	Action::_actCredit()
{
  if (_notConnected())
    return;

  _client->appendBufWrite(_client->getCredit());
  _client->appendBufWrite(NL);
}

void	Action::_actStatus()
{
  if (!_notConnected())
    {
      _client->appendBufWrite(OK);
      _client->appendBufWrite(NL);
    }
}

void	Action::_actClients()
{
  if (_notConnected())
    return;

  _client->appendBufWrite(BEGIN);
  _client->appendBufWrite(NL);

  Server::listClients&	listClients = _server->getListClients();

  for (Server::listClients::const_iterator
	 it = listClients.begin(),
	 end = listClients.end();
       it != end; ++it)
    {
      Client*	client = *it;

      if (client->isConnected())
	{
	  _client->appendBufWrite(client->getLogin());
	  _client->appendBufWrite(NL);
	}
    }

  _client->appendBufWrite(END);
  _client->appendBufWrite(NL);
}

void	Action::_actAccounts()
{
  if (_notConnected())
    return;

  Database*		database = Database::getInstance();
  SQLiteStatement*	stmt =
    database->database().Statement("select username "
				   "from users "
				   "order by username;");

  _client->appendBufWrite(BEGIN);
  _client->appendBufWrite(NL);

  while (stmt->NextRow())
    {
      _client->appendBufWrite(stmt->ValueString(0));
      _client->appendBufWrite(NL);
    }

  stmt->End();

  _client->appendBufWrite(END);
  _client->appendBufWrite(NL);
}

void	Action::_actMessage()
{
  if (_notConnected())
    return;

  std::string	str(_client->getBufRead());
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
      !(to = _server->findClient(login)))
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);
      return;
    }

  to->appendBufWrite(MESSAGE);
  to->appendBufWrite(" ");
  to->appendBufWrite(_client->getLogin());
  to->appendBufWrite(" ");
  to->appendBufWrite(message);
  to->appendBufWrite(NL);

  _client->appendBufWrite(OK);
  _client->appendBufWrite(NL);
}

void	Action::_actWeb()
{
  _sendServices(std::string("select name "
			    "from web "
			    "where id_user = ? "
			    "order by name;"));
}

void	Action::_actStream()
{
  _sendServices(std::string("select name "
			    "from stream "
			    "where id_user = ? "
			    "order by name;"));
}

void	Action::_sendServices(const std::string& req)
{
  if (_notConnected())
    return;

  Database*		database = Database::getInstance();
  SQLiteStatement*	stmt = database->database().Statement(req);

  _client->appendBufWrite(BEGIN);
  _client->appendBufWrite(NL);

  stmt->Bind(0, _client->getId());

  while (stmt->NextRow())
    {
      _client->appendBufWrite(stmt->ValueString(0));
      _client->appendBufWrite(NL);
    }

  stmt->End();

  _client->appendBufWrite(END);
  _client->appendBufWrite(NL);
}

void	Action::_actWebDetail()
{
  if (_notConnected())
    return;

  std::stringstream	ss(_client->getBufRead());
  std::string		action;
  std::string		name;

  ss >> action >> name;

  if (name.empty())
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);

      return;
    }

  Database*		database = Database::getInstance();
  SQLiteStatement*	stmt =
    database->database().Statement("select space, nb_db, domain, "
				   "created, expired "
				   "from web "
				   "where id_user = ? and name = ?;");

  stmt->Bind(0, _client->getId());
  stmt->Bind(1, name);

  if (stmt->NextRow())
    {
      std::stringstream	ss;

      ss << name
	 << ' ' << stmt->ValueString(0)
	 << ' ' << stmt->ValueString(1)
	 << ' ' << stmt->ValueString(2)
	 << ' ' << stmt->ValueString(3)
	 << ' ' << stmt->ValueString(4);

      _client->appendBufWrite(ss.str());
      _client->appendBufWrite(NL);
    }
  else
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);
    }

  stmt->End();
}

void	Action::_actStreamDetail()
{
  if (_notConnected())
    return;

  std::stringstream	ss(_client->getBufRead());
  std::string		action;
  std::string		name;

  ss >> action >> name;

  if (name.empty())
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);

      return;
    }

  Database*		database = Database::getInstance();
  SQLiteStatement*	stmt =
    database->database().Statement("select slots, bits, title, "
				   "port, created, expired "
				   "from stream "
				   "where id_user = ? and name = ?;");

  stmt->Bind(0, _client->getId());
  stmt->Bind(1, name);

  if (stmt->NextRow())
    {
      std::stringstream	ss;

      ss << name
	 << ' ' << stmt->ValueString(0)
	 << ' ' << stmt->ValueString(1)
	 << ' ' << stmt->ValueString(2)
	 << ' ' << stmt->ValueString(3)
	 << ' ' << (_streamOnline(name) ? '1' : '0')
	 << ' ' << stmt->ValueString(4)
	 << ' ' << stmt->ValueString(5);

      _client->appendBufWrite(ss.str());
      _client->appendBufWrite(NL);
    }
  else
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);
    }

  stmt->End();
}

void	Action::_actOfferWeb()
{
  _sendOffer("select name, price "
	     "from offer_web "
	     "order by name;");
}

void	Action::_actOfferStream()
{
  _sendOffer("select name, price "
	     "from offer_stream "
	     "order by name;");
}

void	Action::_sendOffer(const std::string& req)
{
  if (_notConnected())
    return;

  Database*		database = Database::getInstance();
  SQLiteStatement*	stmt = database->database().Statement(req);

  _client->appendBufWrite(BEGIN);
  _client->appendBufWrite(NL);

  while (stmt->NextRow())
    {
      _client->appendBufWrite(stmt->ValueString(0));
      _client->appendBufWrite(SP);
      _client->appendBufWrite(stmt->ValueString(1));
      _client->appendBufWrite(NL);
    }

  stmt->End();

  _client->appendBufWrite(END);
  _client->appendBufWrite(NL);
}

void	Action::_actCreateOfferWeb()
{
  if (_notConnected())
    return;

  std::stringstream	ss(_client->getBufRead());
  std::string		action;
  std::string		name;
  std::string		offer;
  std::string		domain;

  ss >> action >> name >> offer >> domain;

  if (name.empty() || offer.empty() || domain.empty())
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);

      return;
    }

  Database*		database = Database::getInstance();
  SQLiteStatement*	stmt =
    database->database().Statement("select price, space, nb_db "
				   "from offer_web "
				   "where name = ?;");

  stmt->Bind(0, offer);

  bool	ret = stmt->NextRow();

  stmt->End();

  if (!ret)
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);
      return;
    }

  int	price = stmt->ValueInt(0);

  Credit	credit(_client);

  if (!credit.haveEnoughFor(price))
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);
      return;
    }

  int	space = stmt->ValueInt(1);
  int	nbDb = stmt->ValueInt(2);

  stmt = database->database().Statement("insert into web "
					"values(?, ?, ?, ?, ?, ?, ?);");

  stmt->Bind(0, _client->getId());
  stmt->Bind(1, name);
  stmt->Bind(2, space);
  stmt->Bind(3, nbDb);
  stmt->Bind(4, domain);
  stmt->Bind(5, 1);
  stmt->Bind(6, 1);

  stmt->Execute();

  credit.sub(price);

  Apache	serverWeb(_client);

  serverWeb.createHost(domain);

  _client->appendBufWrite(OK);
  _client->appendBufWrite(NL);
}

void	Action::_actCreateWeb()
{
  if (_notConnected())
    return;

  std::stringstream	ss(_client->getBufRead());
  std::string		action;
  std::string		name;
  int			space = 0;
  int			nbDb = 0;
  std::string		domain;

  ss >> action >> name >> space >> nbDb >> domain;

  if (name.empty() || !space || !nbDb || domain.empty())
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);
      return;
    }

  int	price = ((space / RATIO_WEB_SPACE)
		 + (nbDb / RATIO_WEB_DB));

  Credit	credit(_client);

  if (!credit.haveEnoughFor(price))
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);
      return;
    }

  Database*		database = Database::getInstance();
  SQLiteStatement*	stmt =
    database->database().Statement("insert into web "
				   "values(?, ?, ?, ?, ?, ?, ?);");

  stmt->Bind(0, _client->getId());
  stmt->Bind(1, name);
  stmt->Bind(2, space);
  stmt->Bind(3, nbDb);
  stmt->Bind(4, domain);
  stmt->Bind(5, 1);
  stmt->Bind(6, 1);

  stmt->Execute();

  credit.sub(price);

  Apache	serverWeb(_client);

  serverWeb.createHost(domain);

  _client->appendBufWrite(OK);
  _client->appendBufWrite(NL);
}

void	Action::_actCreateOfferStream()
{
  if (_notConnected())
    return;

  std::stringstream	ss(_client->getBufRead());
  std::string		action;
  std::string		offer;
  std::string		name;
  std::string		title;

  ss >> action >> name >> offer >> title;

  if (name.empty() || offer.empty() || title.empty())
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);

      return;
    }

  Database*		database = Database::getInstance();
  SQLiteStatement*	stmt =
    database->database().Statement("select price, slots, bits "
				   "from offer_stream "
				   "where name = ?;");

  stmt->Bind(0, offer);

  bool	ret = stmt->NextRow();

  stmt->End();

  if (!ret)
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);
      return;
    }

  int	price = stmt->ValueInt(0);

  Credit	credit(_client);

  if (!credit.haveEnoughFor(price))
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);
      return;
    }

  Stream	stream;

  stream.setLogin(_client->getLogin());
  stream.setName(name);
  stream.setSlots(stmt->ValueInt(1));
  stream.setBits(stmt->ValueInt(2));
  stream.setTitle(title);

  stmt = database->database().Statement("select max(port) + 2 "
					"from stream;");

  if (!stmt->NextRow())
    stream.setPort(9000);
  else
    stream.setPort(stmt->ValueInt(0));

  stmt->End();

  stmt = database->database().Statement
    ("insert into stream "
     "values(?, ?, ?, ?, ?, ?, ?, ?);");

  stmt->Bind(0, _client->getId());
  stmt->Bind(1, stream.getName());
  stmt->Bind(2, stream.getSlots());
  stmt->Bind(3, stream.getBits());
  stmt->Bind(4, stream.getTitle());
  stmt->Bind(5, stream.getPort());
  stmt->Bind(6, 0);
  stmt->Bind(7, 1);
  stmt->Bind(8, 1);

  stmt->Execute();

  credit.sub(price);

  IceCast	serverStream(stream);

  serverStream.createStream();

  _client->appendBufWrite(OK);
  _client->appendBufWrite(NL);
}

void	Action::_actCreateStream()
{
  if (_notConnected())
    return;

  std::stringstream	ss(_client->getBufRead());
  std::string		action;
  std::string		name;
  int			slots = 0;
  int			bits = 0;
  std::string		title;

  ss >> action >> name >> slots >> bits >> title;

  if (name.empty() || !slots || !bits || title.empty())
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);
      return;
    }

  int	price = ((slots / RATIO_STREAM_SLOT)
		 + (bits / RATIO_STREAM_BITS));

  Credit	credit(_client);

  if (!credit.haveEnoughFor(price))
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);
      return;
    }

  Stream	stream;

  stream.setLogin(_client->getLogin());
  stream.setName(name);
  stream.setSlots(slots);
  stream.setBits(bits);
  stream.setTitle(title);

  Database*		database = Database::getInstance();
  SQLiteStatement*	stmt =
    database->database().Statement("select max(port) + 2 "
				   "from stream;");

  if (!stmt->NextRow())
    stream.setPort(9000);
  else
    stream.setPort(stmt->ValueInt(0));

  stmt->End();

  stmt = database->database().Statement
    ("insert into stream "
     "values(?, ?, ?, ?, ?, ?, ?, ?, ?);");

  stmt->Bind(0, _client->getId());
  stmt->Bind(1, stream.getName());
  stmt->Bind(2, stream.getSlots());
  stmt->Bind(3, stream.getBits());
  stmt->Bind(4, stream.getTitle());
  stmt->Bind(5, stream.getPort());
  stmt->Bind(6, 0);
  stmt->Bind(7, 1);
  stmt->Bind(8, 1);

  stmt->Execute();

  credit.sub(price);

  IceCast	serverStream(stream);

  serverStream.createStream();

  _client->appendBufWrite(OK);
  _client->appendBufWrite(NL);
}

void	Action::_actNews()
{
  if (_notConnected())
    return;

  Database*		database = Database::getInstance();
  SQLiteStatement*	stmt =
    database->database().Statement("select id, date, subject "
				   "from news "
				   "order by date desc;");

  _client->appendBufWrite(BEGIN);
  _client->appendBufWrite(NL);

  while (stmt->NextRow())
    {
      _client->appendBufWrite(stmt->ValueString(0));
      _client->appendBufWrite(SP);
      _client->appendBufWrite(stmt->ValueString(1));
      _client->appendBufWrite(SP);
      _client->appendBufWrite(stmt->ValueString(2));
      _client->appendBufWrite(NL);
    }

  stmt->End();

  _client->appendBufWrite(END);
  _client->appendBufWrite(NL);
}

void	Action::_actNewsDetail()
{
  if (_notConnected())
    return;

  std::stringstream	ss(_client->getBufRead());
  std::string		action;
  int			id = 0;

  ss >> action >> id;

  if (!id)
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);

      return;
    }

  Database*		database = Database::getInstance();
  SQLiteStatement*	stmt =
    database->database().Statement("select body "
				   "from news "
				   "where id = ? "
				   "order by date desc;");

  stmt->Bind(0, id);

  bool	ret = stmt->NextRow();

  stmt->End();

  if (ret)
    {
      _client->appendBufWrite(stmt->ValueString(0));
      _client->appendBufWrite(NL);

      return;
    }

  _client->appendBufWrite(KO);
  _client->appendBufWrite(NL);
}

void	Action::_actStreamStatus()
{
  if (_notConnected())
    return;

  std::stringstream	ss(_client->getBufRead());
  std::string		action;
  std::string		name;

  ss >> action >> name;

  if (_streamOnline(name))
    {
      _client->appendBufWrite(OK);
      _client->appendBufWrite(NL);

      return;
    }

  _client->appendBufWrite(KO);
  _client->appendBufWrite(NL);
}

void	Action::_actStreamStart()
{
  if (_notConnected())
    return;

  std::stringstream	ss(_client->getBufRead());
  std::string		action;
  std::string		name;

  ss >> action >> name;

  if (_streamOnline(name))
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);

      return;
    }

  Server::mapStreamPid&	mapStreamPid = _server->getMapStreamPid();

  if (!(mapStreamPid[name][_client->getLogin()] = ::fork()))
    {
      std::cout << "debug: [" << "I'm the son" << ']' << std::endl;

      std::stringstream	ss;

      ss << "icecast/" << _client->getLogin()
	 << "/" << name << "/icecast.xml";

      ::execl("/usr/local/bin/icecast", "icecast",
	      "-c", ss.str().c_str(), (char*)0);

      //::execl("/usr/bin/yes", "yes", (char*)0);

      std::cerr << "execl error" << std::endl;
      ::exit(-1);
    }
  std::cout << "debug: [" << "I'm the father"
	    << std::endl << "pid child: "
	    << mapStreamPid[name][_client->getLogin()] << ']' << std::endl;

  _client->appendBufWrite(OK);
  _client->appendBufWrite(NL);
}

void	Action::_actStreamStop()
{
  if (_notConnected())
    return;

  std::stringstream	ss(_client->getBufRead());
  std::string		action;
  std::string		name;

  ss >> action >> name;

  if (_streamOnline(name))
    {
      Server::mapStreamPid&	mapStreamPid = _server->getMapStreamPid();
      pid_t&			pid = mapStreamPid[name][_client->getLogin()];

      ::kill(pid, SIGQUIT);

      pid = 0;

      _client->appendBufWrite(OK);
      _client->appendBufWrite(NL);

      return;
    }

  _client->appendBufWrite(KO);
  _client->appendBufWrite(NL);
}

void	Action::_actHalt()
{
  if (_notConnected())
    return;

  _client->appendBufWrite(OK);
  _client->appendBufWrite(NL);

  ::kill(::getpid(), SIGINT);
}

void	Action::_actBreak()
{
  if (_notConnected())
    return;
}

void	Action::_actPlay()
{
  if (_notConnected())
    return;
}

void	Action::_actReload()
{
  if (_notConnected())
    return;
}

std::string	Action::_generatePasswd()
{
  const size_t	size = std::string(PASSWD_CHARACTERS).size();
  std::string	res;

  srand((unsigned int)time(0));
  for (int i = 0; i < PASSWD_SIZE; i++)
    res += PASSWD_CHARACTERS[rand() % size];
  return (res);
}

bool	Action::_streamOnline(const std::string& name)
{
  Server::mapStreamPid&	mapStreamPid = _server->getMapStreamPid();

  if (mapStreamPid.find(name) != mapStreamPid.end())
    {
      Server::mapClientPid&	map = mapStreamPid[name];

      if (map.find(_client->getLogin()) != map.end())
	{
	  pid_t&	pid = map[_client->getLogin()];

	  if (pid)
	    return (true);
	}
    }
  return (false);
}

bool	Action::_existLogin(const std::string& login)
{
  Database*		database = Database::getInstance();
  SQLiteStatement*	stmt =
    database->database().Statement("select 1 "
				   "from users "
				   "where username = ?;");

  stmt->Bind(0, login);

  bool	ret = stmt->NextRow();

  stmt->End();

  return (ret);
}

bool	Action::_existLoginPasswd(const std::string& login,
				  const std::string& passwd)
{
  Database*		database = Database::getInstance();
  SQLiteStatement*	stmt =
    database->database().Statement("select 1 "
				   "from users "
				   "where username = ? "
				   "and password = ?;");

  stmt->Bind(0, login);
  stmt->Bind(1, passwd);

  bool	ret = stmt->NextRow();

  stmt->End();

  return (ret);
}

bool	Action::_alreadyConnected(const std::string& login)
{
  Server::listClients&	listClients = _server->getListClients();

  for (Server::listClients::const_iterator
	 it = listClients.begin(),
	 end = listClients.end();
       it != end; ++it)
    {
      Client*	client = *it;

      if (client->isConnected())
	if (client->getLogin() == login)
	  return (true);
    }
  return (false);
}

bool	Action::_notConnected()
{
  if (!_client->isConnected())
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);

      return (true);
    }
  return (false);
}
