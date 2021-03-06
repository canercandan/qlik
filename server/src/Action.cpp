// Action.cpp --- 
// 
// Filename: Action.cpp
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 01:44:02 2008 (+0200)
// Version: 
// Last-Updated: Thu Dec  4 01:30:17 2008 (+0200)
//           By: Caner Candan
//     Update #: 423
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
  _buffer.str(_client->getBufRead());

  std::string	action;

  _buffer >> action;

  if (_mapAction.find(action) == _mapAction.end())
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);
      return;
    }

  pairCallback	pairCallback(_mapAction[action]);
  callback	callback = pairCallback.first;
  pairParam	pairParam(pairCallback.second);
  bool		connected = pairParam.first;
  int		right = pairParam.second;

  _client->appendBufWrite(action);
  _client->appendBufWrite(SP);

  if ((connected && !_client->isConnected()) ||
      (right != RIGHT_NONE && (_client->getRight() & right) != right))
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);
      return;
    }

  std::string	buffer(_buffer.str());
  size_t	pos;

  pos = buffer.find(SP);
  buffer.erase(0, pos + 1);

  pos = buffer.find(NL);
  buffer.erase(pos);

  _buffer.str(buffer);


  (this->*callback)();
}

void	Action::_fillMapAction()
{
  _mapAction[LOGIN] =
    pairCallback(&Action::_actLogin, pairParam(false, RIGHT_NONE));
  _mapAction[LOGOUT] =
    pairCallback(&Action::_actLogout, pairParam(false, RIGHT_NONE));
  _mapAction[CREATE] =
    pairCallback(&Action::_actCreate, pairParam(false, RIGHT_NONE));

  _mapAction[CREDIT] =
    pairCallback(&Action::_actCredit, pairParam(true, RIGHT_NONE));

  _mapAction[ADD_CREDIT] =
    pairCallback(&Action::_actAddCredit, pairParam(true, RIGHT_NONE));
  _mapAction[LIST_CREDIT] =
    pairCallback(&Action::_actListCredit, pairParam(true, RIGHT_ADMIN));
  _mapAction[ACCEPT_CREDIT] =
    pairCallback(&Action::_actAcceptCredit, pairParam(true, RIGHT_ADMIN));
  _mapAction[REJECT_CREDIT] =
    pairCallback(&Action::_actRejectCredit, pairParam(true, RIGHT_ADMIN));

  _mapAction[STATUS] =
    pairCallback(&Action::_actStatus, pairParam(true, RIGHT_NONE));
  _mapAction[RIGHT] =
    pairCallback(&Action::_actRight, pairParam(true, RIGHT_NONE));

  _mapAction[CLIENTS] =
    pairCallback(&Action::_actClients, pairParam(true, RIGHT_MESSAGE));

  _mapAction[ACCOUNTS] =
    pairCallback(&Action::_actAccounts, pairParam(true, RIGHT_ADMIN));
  _mapAction[ACCOUNTS_MODIFY] =
    pairCallback(&Action::_actAccountsModify, pairParam(true, RIGHT_ADMIN));

  _mapAction[MESSAGE] =
    pairCallback(&Action::_actMessage, pairParam(true, RIGHT_MESSAGE));

  _mapAction[WEB] =
    pairCallback(&Action::_actWeb, pairParam(true, RIGHT_WEB));
  _mapAction[STREAM] =
    pairCallback(&Action::_actStream, pairParam(true, RIGHT_STREAM));

  _mapAction[WEB_DETAIL] =
    pairCallback(&Action::_actWebDetail, pairParam(true, RIGHT_WEB));
  _mapAction[STREAM_DETAIL] =
    pairCallback(&Action::_actStreamDetail, pairParam(true, RIGHT_STREAM));

  _mapAction[OFFER_WEB] =
    pairCallback(&Action::_actOfferWeb, pairParam(true, RIGHT_WEB));
  _mapAction[OFFER_STREAM] =
    pairCallback(&Action::_actOfferStream, pairParam(true, RIGHT_STREAM));

  _mapAction[CREATE_OFFER_WEB] =
    pairCallback(&Action::_actCreateOfferWeb, pairParam(true, RIGHT_WEB));
  _mapAction[CREATE_OFFER_STREAM] =
    pairCallback(&Action::_actCreateOfferStream, pairParam(true, RIGHT_STREAM));

  _mapAction[CREATE_WEB] =
    pairCallback(&Action::_actCreateWeb, pairParam(true, RIGHT_WEB));
  _mapAction[CREATE_STREAM] =
    pairCallback(&Action::_actCreateStream, pairParam(true, RIGHT_STREAM));

  _mapAction[RENEW_WEB] =
    pairCallback(&Action::_actRenewWeb, pairParam(true, RIGHT_WEB));
  _mapAction[RENEW_STREAM] =
    pairCallback(&Action::_actRenewStream, pairParam(true, RIGHT_STREAM));

  _mapAction[NEWS] =
    pairCallback(&Action::_actNews, pairParam(true, RIGHT_NEWS));
  _mapAction[NEWS_DETAIL] =
    pairCallback(&Action::_actNewsDetail, pairParam(true, RIGHT_NEWS));
  _mapAction[NEWS_ADD] =
    pairCallback(&Action::_actNewsAdd,
		 pairParam(true, RIGHT_NEWS | RIGHT_ADMIN));
  _mapAction[NEWS_DELETE] =
    pairCallback(&Action::_actNewsDelete,
		 pairParam(true, RIGHT_NEWS | RIGHT_ADMIN));

  _mapAction[WEB_STATUS] =
    pairCallback(&Action::_actWebStatus, pairParam(true, RIGHT_WEB));
  _mapAction[WEB_START] =
    pairCallback(&Action::_actWebStart, pairParam(true, RIGHT_WEB));
  _mapAction[WEB_STOP] =
    pairCallback(&Action::_actWebStop, pairParam(true, RIGHT_WEB));

  _mapAction[STREAM_STATUS] =
    pairCallback(&Action::_actStreamStatus, pairParam(true, RIGHT_STREAM));
  _mapAction[STREAM_START] =
    pairCallback(&Action::_actStreamStart, pairParam(true, RIGHT_STREAM));
  _mapAction[STREAM_STOP] =
    pairCallback(&Action::_actStreamStop, pairParam(true, RIGHT_STREAM));

  _mapAction[HALT] =
    pairCallback(&Action::_actHalt, pairParam(true, RIGHT_SERVER));
  _mapAction[BREAK] =
    pairCallback(&Action::_actBreak, pairParam(true, RIGHT_SERVER));
  _mapAction[PLAY] =
    pairCallback(&Action::_actPlay, pairParam(true, RIGHT_SERVER));
  _mapAction[RELOAD] =
    pairCallback(&Action::_actReload, pairParam(true, RIGHT_SERVER));
}

void	Action::_actLogin()
{
  std::string	login;
  std::string	passwd;

  _buffer >> login >> passwd;

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
    database->database().Statement("select id, username, "
				   "credit, right "
				   "from users "
				   "where username = ?;");

  stmt->Bind(0, login);

  if (stmt->NextRow())
    {
      _client->setId(stmt->ValueInt(0));
      _client->setLogin(stmt->ValueString(1));
      _client->setCredit(stmt->ValueInt(2));
      _client->setRight(stmt->ValueInt(3));
    }

  stmt->End();

  _client->appendBufWrite(_client->getCredit());
  _client->appendBufWrite(SP);
  _client->appendBufWrite(_client->getRight());
  _client->appendBufWrite(NL);

  _reloadClientsList();
  _reloadAccountsList();
}

void	Action::_actLogout()
{
  _client->setLogin(EMPTY);

  _client->appendBufWrite(OK);
  _client->appendBufWrite(NL);

  _reloadClientsList();
  _reloadAccountsList();
}

void	Action::_actCreate()
{
  std::string	login;
  std::string	passwd;

  _buffer >> login;

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
				   "values(NULL, ?, ?, 0, ?);");

  stmt->Bind(0, login);
  stmt->Bind(1, passwd);

  int	right = 0;

  right |= RIGHT_MESSAGE;
  //right |= RIGHT_WEB;
  right |= RIGHT_STREAM;
  right |= RIGHT_NEWS;

  stmt->Bind(2, right);

  stmt->Execute();

  _client->appendBufWrite(passwd);
  _client->appendBufWrite(NL);

  _reloadAccountsList();
}

void	Action::_actCredit()
{
  _client->appendBufWrite(_client->getCredit());
  _client->appendBufWrite(NL);
}

void	Action::_actAddCredit()
{
  int	credit = 0;

  _buffer >> credit;

  Database*		database = Database::getInstance();
  SQLiteStatement*	stmt =
    database->database().Statement("insert into credits "
				   "values(null, ?, ?, ?);");

  stmt->Bind(0, _client->getId());
  stmt->Bind(1, credit);
  stmt->Bind(2, (int)time(0));

  stmt->Execute();

  _client->appendBufWrite(OK);
  _client->appendBufWrite(NL);

  _reloadCreditList();
}

void	Action::_actListCredit()
{
  Database*		database = Database::getInstance();
  SQLiteStatement*	stmt =
    database->database().Statement("select c.id, u.username, u.credit, "
				   "c.credit, c.date "
				   "from credits c, users u "
				   "where c.id_user = u.id;");

  _client->appendBufWrite(BEGIN);
  _client->appendBufWrite(NL);

  while (stmt->NextRow())
    {
      _client->appendBufWrite(stmt->ValueInt(0));
      _client->appendBufWrite(SP);
      _client->appendBufWrite(stmt->ValueString(1));
      _client->appendBufWrite(SP);
      _client->appendBufWrite(stmt->ValueInt(2));
      _client->appendBufWrite(SP);
      _client->appendBufWrite(stmt->ValueInt(3));
      _client->appendBufWrite(SP);
      _client->appendBufWrite(stmt->ValueInt(4));
      _client->appendBufWrite(NL);
    }

  stmt->End();

  _client->appendBufWrite(END);
  _client->appendBufWrite(NL);
}

void	Action::_actAcceptCredit()
{
  int	id = 0;

  _buffer >> id;

  Database*		database = Database::getInstance();
  SQLiteStatement*	stmt =
    database->database().Statement("select id_user, credit "
				   "from credits "
				   "where id = ?;");

  stmt->Bind(0, id);

  if (!stmt->NextRow())
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);

      stmt->End();

      return;
    }

  int	idUser = stmt->ValueInt(0);
  int	credit = stmt->ValueInt(1);

  stmt->End();

  _acceptCredit(idUser, credit);
  _rejectCredit(id);

  stmt = database->database().Statement("delete from credits "
					"where id = ?;");

  stmt->Bind(0, id);

  stmt->Execute();

  _client->appendBufWrite(OK);
  _client->appendBufWrite(NL);

  Client*	client = _server->findClient(idUser);

  _reloadCredit(client);
  _reloadAccountsList();
  _reloadCreditList();
}

void	Action::_actRejectCredit()
{
  int	id = 0;

  _buffer >> id;

  _rejectCredit(id);

  _client->appendBufWrite(OK);
  _client->appendBufWrite(NL);

  _reloadCreditList();
}

void	Action::_acceptCredit(const int idUser, const int credit)
{
  Database*		database = Database::getInstance();
  SQLiteStatement*	stmt =
    database->database().Statement("update users "
				   "set credit = credit + ? "
				   "where id = ?;");

  stmt->Bind(0, credit);
  stmt->Bind(1, idUser);

  stmt->Execute();
}

void	Action::_rejectCredit(const int id)
{
  Database*		database = Database::getInstance();
  SQLiteStatement*	stmt =
    database->database().Statement("delete from credits "
				   "where id = ?;");

  stmt->Bind(0, id);

  stmt->Execute();
}

void	Action::_reloadCredit(Client* client)
{
  if (!client)
    return;

  Client*	oldClient = _client;

  _client = client;

  _client->syncCredit();
  _client->appendBufWrite(CREDIT);
  _client->appendBufWrite(SP);
  _actCredit();

  _client = oldClient;
}

void	Action::_reloadRight(Client* client)
{
  if (!client)
    return;

  Client*	oldClient = _client;

  _client = client;

  _client->syncRight();
  _client->appendBufWrite(RIGHT);
  _client->appendBufWrite(SP);
  _actRight();

  _client = oldClient;
}

void	Action::_reloadClientsList()
{
  Server::listClients&	listClients = _server->getListClients();

  for (Server::listClients::iterator
	 it = listClients.begin(),
	 end = listClients.end();
       it != end; ++it)
    {
      Client*	client = *it;

      if (!client)
	continue;

      if (!client->isConnected())
	continue;

      if (_client->getLogin() == client->getLogin())
	continue;

      Client*	oldClient = _client;

      _client = client;

      _client->appendBufWrite(CLIENTS);
      _client->appendBufWrite(SP);

      _actClients();

      _client = oldClient;
    }
}

void	Action::_reloadAccountsList()
{
  Server::listClients&	listClients = _server->getListClients();

  for (Server::listClients::iterator
	 it = listClients.begin(),
	 end = listClients.end();
       it != end; ++it)
    {
      Client*	client = *it;

      if (!client)
	continue;

      if (!client->isConnected())
	continue;

      if ((client->getRight() & RIGHT_ADMIN) != RIGHT_ADMIN)
	continue;

      Client*	oldClient = _client;

      _client = client;

      _client->appendBufWrite(ACCOUNTS);
      _client->appendBufWrite(SP);

      _actAccounts();

      _client = oldClient;
    }
}

void	Action::_reloadCreditList()
{
  Server::listClients&	listClients = _server->getListClients();

  for (Server::listClients::iterator
	 it = listClients.begin(),
	 end = listClients.end();
       it != end; ++it)
    {
      Client*	client = *it;

      if (!client)
	continue;

      if (!client->isConnected())
	continue;

      if ((client->getRight() & RIGHT_ADMIN) != RIGHT_ADMIN)
	continue;

      Client*	oldClient = _client;

      _client = client;

      _client->appendBufWrite(LIST_CREDIT);
      _client->appendBufWrite(SP);

      _actListCredit();

      _client = oldClient;
    }
}

void	Action::_reloadWebList()
{
  _client->syncCredit();
  _client->appendBufWrite(WEB);
  _client->appendBufWrite(SP);
  _actWeb();
}

void	Action::_reloadStreamList()
{
  _client->syncCredit();
  _client->appendBufWrite(STREAM);
  _client->appendBufWrite(SP);
  _actStream();
}

void	Action::_reloadNewsList()
{
  Server::listClients&	listClients = _server->getListClients();

  for (Server::listClients::iterator
	 it = listClients.begin(),
	 end = listClients.end();
       it != end; ++it)
    {
      Client*	client = *it;

      if (!client)
	continue;

      if (!client->isConnected())
	continue;

      Client*	oldClient = _client;

      _client = client;

      _client->appendBufWrite(NEWS);
      _client->appendBufWrite(SP);

      _actNews();

      _client = oldClient;
    }
}

void	Action::_actStatus()
{
  _client->appendBufWrite(OK);
  _client->appendBufWrite(NL);
}

void	Action::_actRight()
{
  _client->appendBufWrite(_client->getRight());
  _client->appendBufWrite(NL);
}

void	Action::_actClients()
{
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
	  _client->appendBufWrite(SP);
	  _client->appendBufWrite(client->getRight());
	  _client->appendBufWrite(NL);
	}
    }

  _client->appendBufWrite(END);
  _client->appendBufWrite(NL);
}

void	Action::_actAccounts()
{
  Database*		database = Database::getInstance();
  SQLiteStatement*	stmt =
    database->database().Statement("select username, credit, right "
				   "from users "
				   "order by username;");

  _client->appendBufWrite(BEGIN);
  _client->appendBufWrite(NL);

  while (stmt->NextRow())
    {
      _client->appendBufWrite(stmt->ValueString(0));
      _client->appendBufWrite(SP);
      _client->appendBufWrite(stmt->ValueString(1));
      _client->appendBufWrite(SP);
      _client->appendBufWrite(stmt->ValueString(2));
      _client->appendBufWrite(SP);
      _client->appendBufWrite(_server->findClient
			      (stmt->ValueString(0)) ? 1 : 0);
      _client->appendBufWrite(NL);
    }

  stmt->End();

  _client->appendBufWrite(END);
  _client->appendBufWrite(NL);
}

void	Action::_actAccountsModify()
{
  std::string	account;
  int		credit = -1;
  int		right = -1;

  _buffer >> account >> credit >> right;

  if (account.empty() || credit == -1 || right == -1)
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);
      return;
    }

  Database*		database = Database::getInstance();
  SQLiteStatement*	stmt =
    database->database().Statement("update users "
				   "set credit = ?, right = ? "
				   "where username = ?;");

  stmt->Bind(0, credit);
  stmt->Bind(1, right);
  stmt->Bind(2, account);

  stmt->Execute();

  _client->appendBufWrite(OK);
  _client->appendBufWrite(NL);

  Client*	client = _server->findClient(account);

  _reloadCredit(client);
  _reloadRight(client);
  _reloadAccountsList();
  _reloadClientsList();
}

void	Action::_actMessage()
{
  std::string	str(_buffer.str());
  size_t	separator = str.find(SP);
  std::string	login(str.substr(0, separator));
  std::string	message(str.substr(separator + 1));
  Client*	to;

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
  std::string	name;

  _buffer >> name;

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
  std::string	name;

  _buffer >> name;

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
  std::string	name;
  std::string	offer;
  std::string	domain;

  _buffer >> name >> offer >> domain;

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

  if (!stmt->NextRow())
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);

      stmt->End();

      return;
    }

  Web	web;

  web.setPrice(stmt->ValueInt(0));
  web.setName(name);
  web.setSpace(stmt->ValueInt(1));
  web.setNbDb(stmt->ValueInt(2));
  web.setDomain(domain);

  stmt->End();

  _createWeb(web);
}

void	Action::_actCreateWeb()
{
  std::string	name;
  int		space = 0;
  int		nbDb = 0;
  std::string	domain;

  _buffer >> name >> space >> nbDb >> domain;

  if (name.empty() || !space || !nbDb || domain.empty())
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);
      return;
    }

  Web	web;

  web.setPrice((space / RATIO_WEB_SPACE) + (nbDb / RATIO_WEB_DB));
  web.setName(name);
  web.setSpace(space);
  web.setNbDb(nbDb);
  web.setDomain(domain);

  _createWeb(web);
}

void	Action::_createWeb(Web& web)
{
  Credit	credit(_client);

  if (!credit.haveEnoughFor(web.getPrice()))
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);
      return;
    }

  web.setLogin(_client->getLogin());
  web.setCreated((int)time(0));
  web.setExpired(web.getCreated());

  _renewExpiredDate(web);


  Database*		database = Database::getInstance();
  SQLiteStatement*	stmt =
    database->database().Statement("insert into web "
				   "values(?, ?, ?, ?, ?, ?, ?);");

  stmt->Bind(0, _client->getId());
  stmt->Bind(1, web.getName());
  stmt->Bind(2, web.getSpace());
  stmt->Bind(3, web.getNbDb());
  stmt->Bind(4, web.getDomain());
  stmt->Bind(5, web.getCreated());
  stmt->Bind(6, web.getExpired());

  stmt->Execute();

  credit.sub(web.getPrice());

  Apache	serverWeb(_client);

  serverWeb.createHost(web.getDomain());

  _actCredit();

  _reloadWebList();
}

void	Action::_actCreateOfferStream()
{
  std::string	offer;
  std::string	name;
  std::string	title;

  _buffer >> name >> offer >> title;

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

  if (!stmt->NextRow())
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);

      stmt->End();

      return;
    }

  Stream	stream;

  stream.setPrice(stmt->ValueInt(0));
  stream.setName(name);
  stream.setSlots(stmt->ValueInt(1));
  stream.setBits(stmt->ValueInt(2));
  stream.setTitle(title);

  stmt->End();

  _createStream(stream);
}

void	Action::_actCreateStream()
{
  std::string	name;
  int		slots = 0;
  int		bits = 0;
  std::string	title;

  _buffer >> name >> slots >> bits >> title;

  if (name.empty() || !slots || !bits || title.empty())
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);
      return;
    }

  Stream	stream;

  stream.setPrice((slots / RATIO_STREAM_SLOT) + (bits / RATIO_STREAM_BITS));
  stream.setName(name);
  stream.setSlots(slots);
  stream.setBits(bits);
  stream.setTitle(title);

  _createStream(stream);
}

void	Action::_createStream(Stream& stream)
{
  Credit	credit(_client);

  if (!credit.haveEnoughFor(stream.getPrice()))
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);
      return;
    }

  Database*		database = Database::getInstance();
  SQLiteStatement*	stmt =
    database->database().Statement("select max(port) + 2 "
				   "from stream;");

  if (!stmt->NextRow() || stmt->ValueInt(0) == 0)
    stream.setPort(9000);
  else
    stream.setPort(stmt->ValueInt(0));

  stmt->End();

  stream.setLogin(_client->getLogin());
  stream.setCreated((int)time(0));
  stream.setExpired(stream.getCreated());

  _renewExpiredDate(stream);

  stmt = database->database().Statement("insert into stream "
					"values(?, ?, ?, ?, ?, ?, ?, ?);");

  stmt->Bind(0, _client->getId());
  stmt->Bind(1, stream.getName());
  stmt->Bind(2, stream.getSlots());
  stmt->Bind(3, stream.getBits());
  stmt->Bind(4, stream.getTitle());
  stmt->Bind(5, stream.getPort());
  stmt->Bind(6, stream.getCreated());
  stmt->Bind(7, stream.getExpired());

  stmt->Execute();

  credit.sub(stream.getPrice());

  IceCast	serverStream(stream);

  serverStream.createStream();

  _actCredit();

  _reloadStreamList();
}

void	Action::_actRenewWeb()
{
  std::string	name;

  _buffer >> name;

  if (name.empty())
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);
      return;
    }

  Database*		database = Database::getInstance();
  SQLiteStatement*	stmt =
    database->database().Statement("select space, nb_db, expired "
				   "from web "
				   "where id_user = ? and name = ?;");

  stmt->Bind(0, _client->getId());
  stmt->Bind(1, name);

  if (!stmt->NextRow())
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);

      stmt->End();

      return;
    }

  Web	web;

  web.setName(name);
  web.setSpace(stmt->ValueInt(0));
  web.setNbDb(stmt->ValueInt(1));
  web.setExpired(stmt->ValueInt(2));

  web.setPrice((web.getSpace() / RATIO_WEB_SPACE) +
	       (web.getNbDb() / RATIO_WEB_DB));

  stmt->End();

  Credit	credit(_client);

  if (!credit.haveEnoughFor(web.getPrice()))
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);
      return;
    }

  _renewExpiredDate(web);

  stmt = database->database().Statement("update web "
					"set expired = ? "
					"where id_user = ? and name = ?;");

  stmt->Bind(0, web.getExpired());
  stmt->Bind(1, _client->getId());
  stmt->Bind(2, web.getName());

  stmt->Execute();

  credit.sub(web.getPrice());

  _actCredit();
}

void	Action::_actRenewStream()
{
  std::string	name;

  _buffer >> name;

  if (name.empty())
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);
      return;
    }

  Database*		database = Database::getInstance();
  SQLiteStatement*	stmt =
    database->database().Statement("select slots, bits, expired "
				   "from stream "
				   "where id_user = ? and name = ?;");

  stmt->Bind(0, _client->getId());
  stmt->Bind(1, name);

  if (!stmt->NextRow())
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);

      stmt->End();

      return;
    }

  Stream	stream;

  stream.setName(name);
  stream.setSlots(stmt->ValueInt(0));
  stream.setBits(stmt->ValueInt(1));
  stream.setExpired(stmt->ValueInt(2));

  stream.setPrice((stream.getSlots() / RATIO_STREAM_SLOT) +
		  (stream.getBits() / RATIO_STREAM_BITS));

  stmt->End();

  Credit	credit(_client);

  if (!credit.haveEnoughFor(stream.getPrice()))
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);
      return;
    }

  _renewExpiredDate(stream);

  stmt = database->database().Statement("update stream "
					"set expired = ? "
					"where id_user = ? and name = ?;");

  stmt->Bind(0, stream.getExpired());
  stmt->Bind(1, _client->getId());
  stmt->Bind(2, stream.getName());

  stmt->Execute();

  credit.sub(stream.getPrice());

  _actCredit();
}

void	Action::_renewExpiredDate(Service& service)
{
  const int	month = 60 * 60 * 24 * 30.5;

  service.setExpired(service.getExpired() + month);
}

void	Action::_actNews()
{
  Database*		database = Database::getInstance();
  SQLiteStatement*	stmt =
    database->database().Statement("select n.id, u.username, "
				   "n.date, n.subject "
				   "from news n, users u "
				   "where n.id_user = u.id "
				   "order by n.date desc;");

  _client->appendBufWrite(BEGIN);
  _client->appendBufWrite(NL);

  while (stmt->NextRow())
    {
      _client->appendBufWrite(stmt->ValueString(0));
      _client->appendBufWrite(SP);
      _client->appendBufWrite(stmt->ValueString(1));
      _client->appendBufWrite(SP);
      _client->appendBufWrite(stmt->ValueString(2));
      _client->appendBufWrite(SP);
      _client->appendBufWrite(stmt->ValueString(3));
      _client->appendBufWrite(NL);
    }

  stmt->End();

  _client->appendBufWrite(END);
  _client->appendBufWrite(NL);
}

void	Action::_actNewsDetail()
{
  int	id = 0;

  _buffer >> id;

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
				   "where id = ?;");

  stmt->Bind(0, id);

  bool		ret = stmt->NextRow();
  std::string	body(stmt->ValueString(0));

  stmt->End();

  if (ret)
    {
      _client->appendBufWrite(body);
      _client->appendBufWrite(NL);
      return;
    }

  _client->appendBufWrite(KO);
  _client->appendBufWrite(NL);
}

void	Action::_actNewsAdd()
{
  std::string	str(_buffer.str());

  std::cout << "actNewsAdd [" << str << ']' << std::endl;

  size_t	separator = str.find(SP);
  std::string	subject(str.substr(0, separator));
  std::string	body(str.substr(separator + 1));

  std::cout << "actNewsAdd 2 [" << subject << "] [" << body << ']' << std::endl;

  if (subject.empty() || body.empty())
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);
      return;
    }

  Database*		database = Database::getInstance();
  SQLiteStatement*	stmt =
    database->database().Statement("insert into news "
				   "values(null, ?, ?, ?, ?);");

  stmt->Bind(0, _client->getId());
  stmt->Bind(1, subject);
  stmt->Bind(2, body);
  stmt->Bind(3, (int)time(0));

  stmt->Execute();

  _client->appendBufWrite(OK);
  _client->appendBufWrite(NL);

  _reloadNewsList();
}

void	Action::_actNewsDelete()
{
  int	id = 0;

  _buffer >> id;

  if (id == 0)
    {
      _client->appendBufWrite(KO);
      _client->appendBufWrite(NL);

      return;
    }

  Database*		database = Database::getInstance();
  SQLiteStatement*	stmt =
    database->database().Statement("delete from news "
				   "where id = ?;");

  stmt->Bind(0, id);
  stmt->Bind(1, _client->getId());

  stmt->Execute();

  _client->appendBufWrite(OK);
  _client->appendBufWrite(NL);

  _reloadNewsList();
}

void	Action::_actWebStatus()
{}

void	Action::_actWebStart()
{}

void	Action::_actWebStop()
{}

void	Action::_actStreamStatus()
{
  std::string	name;

  _buffer >> name;

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
  std::string	name;

  _buffer >> name;

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
  std::string	name;

  _buffer >> name;

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
  _client->appendBufWrite(OK);
  _client->appendBufWrite(NL);

  ::kill(::getpid(), SIGINT);
}

void	Action::_actBreak()
{
  _client->appendBufWrite(OK);
  _client->appendBufWrite(NL);
}

void	Action::_actPlay()
{
  _client->appendBufWrite(OK);
  _client->appendBufWrite(NL);
}

void	Action::_actReload()
{
  _client->appendBufWrite(OK);
  _client->appendBufWrite(NL);
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

// 
// Action.cpp ends here
