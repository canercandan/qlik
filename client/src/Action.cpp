// Action.cpp --- 
// 
// Filename: Action.cpp
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 00:37:41 2008 (+0200)
// Version: 
// Last-Updated: Thu Dec  4 00:26:17 2008 (+0200)
//           By: Caner Candan
//     Update #: 217
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
// 28-Nov-2008    Caner Candan  
//    Last-Updated: Thu Nov 27 00:43:20 2008 (+0200) #1 (Caner Candan)
//    Reconize expiration and creation date of services
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

#include <QMessageBox>
#include "Action.h"
#include "Protocole.h"
#include "Socket.h"
#include "Database.h"
#include "Accounts.h"
#include "Web.h"
#include "Stream.h"
#include "Service.h"
#include "State.h"
#include "News.h"
#include "AccountsAdmin.h"
#include "Credit.h"

Action::Action(Client* client, const QString& userCreated)
  : _client(client), _userCreated(userCreated)
{
  _fillMapAction();
}

void	Action::execute()
{
  static callback	func = NULL;
  Socket*		socket = Socket::getInstance();

  while (socket->socket()->canReadLine())
    {
      QString	res(socket->socket()->readLine());

      qDebug() << "res" << res;

      QStringList	resList(res.split(QRegExp("\\s+")));
      QString		action(resList.at(0));

      if (func)
	{
	  if (action == END)
	    {
	      qDebug() << "i stop";
	      func = NULL;
	    }
	  else
	    {
	      _resList = resList;
	      (this->*func)();
	    }
	}
      else
	{
	  if (_mapAction.find(action) == _mapAction.end())
	    return;

	  pairCallback	pairCallback(_mapAction[action]);
	  callback	callback = pairCallback.first;
	  int		right = pairCallback.second;

	  qDebug() << "action found" << action;

	  if ((_client->getRight() & right) != right)
	    {
	      qDebug() << "action forbidden";

	      QMessageBox::critical(_client,
				    tr("action_forbidden"),
				    tr("action_forbidden_txt"));
	      return;
	    }

	  resList.erase(resList.begin());

	  if (resList.at(0) == BEGIN)
	    {
	      qDebug() << "i start";
	      resList.erase(resList.begin());
	      func = callback;
	      _initialize(action);
	    }
	  else
	    {
	      _resList = resList;
	      (this->*callback)();
	    }
	}
    }
}

void	Action::_fillMapAction()
{
  _mapAction[WELCOME] = pairCallback(&Action::_actWelcome, RIGHT_NONE);

  _mapAction[LOGIN] = pairCallback(&Action::_actLogin, RIGHT_NONE);
  _mapAction[LOGOUT] = pairCallback(&Action::_actLogout, RIGHT_NONE);
  _mapAction[CREATE] = pairCallback(&Action::_actCreate, RIGHT_NONE);

  _mapAction[CREDIT] = pairCallback(&Action::_actCredit, RIGHT_NONE);

  _mapAction[ADD_CREDIT] = pairCallback(&Action::_actAddCredit, RIGHT_NONE);
  _mapAction[LIST_CREDIT] = pairCallback(&Action::_actListCredit, RIGHT_NONE);
  _mapAction[ACCEPT_CREDIT] =
    pairCallback(&Action::_actAcceptCredit, RIGHT_NONE);
  _mapAction[REJECT_CREDIT] =
    pairCallback(&Action::_actRejectCredit, RIGHT_NONE);

  _mapAction[STATUS] = pairCallback(&Action::_actStatus, RIGHT_NONE);
  _mapAction[RIGHT] = pairCallback(&Action::_actRight, RIGHT_NONE);

  _mapAction[CLIENTS] = pairCallback(&Action::_actClients, RIGHT_MESSAGE);

  _mapAction[ACCOUNTS] = pairCallback(&Action::_actAccounts, RIGHT_ADMIN);
  _mapAction[ACCOUNTS_MODIFY] =
    pairCallback(&Action::_actAccountsModify, RIGHT_ADMIN);

  _mapAction[MESSAGE] = pairCallback(&Action::_actMessage, RIGHT_MESSAGE);

  _mapAction[WEB] = pairCallback(&Action::_actWeb, RIGHT_WEB);
  _mapAction[STREAM] = pairCallback(&Action::_actStream, RIGHT_STREAM);

  _mapAction[WEB_DETAIL] = pairCallback(&Action::_actWebDetail, RIGHT_WEB);
  _mapAction[STREAM_DETAIL] =
    pairCallback(&Action::_actStreamDetail, RIGHT_STREAM);

  _mapAction[OFFER_WEB] = pairCallback(&Action::_actOfferWeb, RIGHT_WEB);
  _mapAction[OFFER_STREAM] =
    pairCallback(&Action::_actOfferStream, RIGHT_STREAM);

  _mapAction[CREATE_OFFER_WEB] =
    pairCallback(&Action::_actCreateOfferWeb, RIGHT_WEB);
  _mapAction[CREATE_OFFER_STREAM] =
    pairCallback(&Action::_actCreateOfferStream, RIGHT_STREAM);

  _mapAction[CREATE_WEB] =
    pairCallback(&Action::_actCreateWeb, RIGHT_WEB);
  _mapAction[CREATE_STREAM] =
    pairCallback(&Action::_actCreateStream, RIGHT_STREAM);

  _mapAction[RENEW_WEB] =
    pairCallback(&Action::_actRenewWeb, RIGHT_WEB);
  _mapAction[RENEW_STREAM] =
    pairCallback(&Action::_actRenewStream, RIGHT_STREAM);

  _mapAction[NEWS] = pairCallback(&Action::_actNews, RIGHT_NEWS);
  _mapAction[NEWS_DETAIL] = pairCallback(&Action::_actNewsDetail, RIGHT_NEWS);
  _mapAction[NEWS_ADD] =
    pairCallback(&Action::_actNewsAdd, RIGHT_NEWS | RIGHT_ADMIN);
  _mapAction[NEWS_DELETE] =
    pairCallback(&Action::_actNewsDelete, RIGHT_NEWS | RIGHT_ADMIN);

  _mapAction[STREAM_STATUS] =
    pairCallback(&Action::_actStreamStatus, RIGHT_STREAM);
  _mapAction[STREAM_START] =
    pairCallback(&Action::_actStreamStart, RIGHT_STREAM);
  _mapAction[STREAM_STOP] =
    pairCallback(&Action::_actStreamStop, RIGHT_STREAM);

  _mapAction[HALT] = pairCallback(&Action::_actHalt, RIGHT_SERVER);
  _mapAction[RELOAD] = pairCallback(&Action::_actReload, RIGHT_SERVER);
  _mapAction[PLAY] = pairCallback(&Action::_actPlay, RIGHT_SERVER);
  _mapAction[BREAK] = pairCallback(&Action::_actBreak, RIGHT_SERVER);
}

void	Action::_initialize(const QString& action)
{
  State*	state = State::getInstance();

  if (action == NEWS)
    {
      state->setNewsList(State::DONE);
      _client->newsList->clear();
    }
  else if (action == CLIENTS)
    {
      state->setClientsList(State::DONE);
      _client->talkMyContactsList->clear();
      _client->talkAllContactsList->clear();
    }
  else if (action == ACCOUNTS)
    {
      state->setAccountsList(State::DONE);
      _client->adminAccountList->clear();
    }
  else if (action == LIST_CREDIT)
    {
      state->setCreditList(State::DONE);
      _client->adminCreditList->clear();
    }
  else if (action == WEB)
    {
      state->setWebList(State::DONE);
      _client->serviceWebList->clear();
    }
  else if (action == STREAM)
    {
      state->setStreamList(State::DONE);
      _client->serviceStreamList->clear();
    }
  else if (action == OFFER_WEB || action == OFFER_STREAM)
    {
      Service*	service = Service::getInstance(_client);

      if (action == OFFER_WEB)
	{
	  state->setOfferWebList(State::DONE);
	  service->offerWebList->clear();
	}
      else
	{
	  state->setOfferStreamList(State::DONE);
	  service->offerStreamList->clear();
	}
    }
}

void	Action::_actWelcome()
{
  _client->statusbar->showMessage(tr("welcome"));
}

void	Action::_actLogin()
{
  if (_resList.at(0) == KO)
    {
      QMessageBox::critical(_client, tr("login_inc"), tr("login_inc_txt"));
      _client->logout();
      return;
    }

  _client->setCredit(_resList.at(0).toInt());
  _client->setRight(_resList.at(1).toInt());

  _client->login();
}

void	Action::_actLogout()
{
  if (_resList.at(0) != OK)
    {
      QMessageBox::critical(_client, tr("logout_err"), tr("logout_err_txt"));
      return;
    }
  _client->logout();
}

void	Action::_actCreate()
{
  if (_resList.at(0) == KO)
    {
      QMessageBox::critical(_client, tr("create_inc"), tr("create_inc_txt"));
      return;
    }
  if (QMessageBox::question(_client, tr("created"), tr("created_txt")
			    + _resList.at(0)
			    + tr("created_txt2"),
			    QMessageBox::Yes | QMessageBox::No)
      == QMessageBox::Yes)
    {
      QSqlQuery	q(Database::getInstance()->database());

      q.prepare("insert into users "
		"values(?, ?);");
      q.addBindValue(_userCreated);
      q.addBindValue(_resList.at(0));
      q.exec();
      Accounts::getInstance(_client)->reset();
    }
  _client->statusbar->showMessage(tr("bar_created"));
}

void	Action::_actCredit()
{
  if (_resList.at(0) == KO)
    return;

  int	credit = _resList.at(0).toInt();

  if (credit == _client->getCredit())
    return;

  _client->setCredit(credit);

  QMessageBox::information(_client, tr("credit"), tr("credit_txt"));
}

void	Action::_actAddCredit()
{
  if (_resList.at(0) == KO)
    {
      QMessageBox::critical(_client,
			    tr("add_credit_err"),
			    tr("add_credit_err_txt"));
      return;
    }

  QMessageBox::information(_client,
			   tr("add_credit"),
			   tr("add_credit_txt"));

  Credit::getInstance()->hide();
}

void	Action::_actListCredit()
{
  if (_resList.count() < 1)
    return;

  const QString	id(_resList.at(0));
  const QString	username(_resList.at(1));
  const QString	currentCredit(_resList.at(2));
  const QString	addCredit(_resList.at(3));

  QDateTime	date;

  date.setTime_t(_resList.at(4).toInt());

  qDebug() << "add in list credit" << id;

  QTreeWidgetItem*	item = new QTreeWidgetItem;

  item->setIcon(0, QIcon(":/admin/images/user.png"));
  item->setData(0, Qt::UserRole, id);

  item->setText(0, username);
  item->setText(1, currentCredit);
  item->setText(2, addCredit);
  item->setText(3, date.toString());

  _client->adminCreditList->addTopLevelItem(item);
}

void	Action::_actAcceptCredit()
{
  if (_resList.at(0) == KO)
    {
      QMessageBox::critical(_client,
			    tr("accept_credit_err"),
			    tr("accept_credit_err_txt"));
      return;
    }

  QMessageBox::information(_client,
			   tr("accept_credit"),
			   tr("accept_credit_txt"));
}

void	Action::_actRejectCredit()
{
  if (_resList.at(0) == KO)
    {
      QMessageBox::critical(_client,
			    tr("reject_credit_err"),
			    tr("reject_credit_err_txt"));
      return;
    }

  QMessageBox::information(_client,
			   tr("reject_credit"),
			   tr("reject_credit_txt"));
}

void	Action::_actStatus()
{}

void	Action::_actRight()
{
  if (_resList.at(0) == KO)
    return;

  int	right = _resList.at(0).toInt();

  if (right == _client->getRight())
    return;

  _client->setRight(right);

  QMessageBox::information(_client, tr("right"), tr("right_txt"));
}

void	Action::_actClients()
{
  if (_resList.count() < 1)
    return;

  const QString	name(_resList.at(0));
  const int	right = _resList.at(1).toInt();

  if (name == _client->infoAccount->text())
    return;

  qDebug() << "add client" << name;

  _client->loadAllContact(name, right);
  _client->loadMyContact(name, right);
}

void	Action::_actAccounts()
{
  if (_resList.count() < 1)
    return;

  const QString	account(_resList.at(0));

  if (account == KO)
    {
      QMessageBox::critical(_client,
			    tr("accounts_err"),
			    tr("accounts_err_txt"));
      return;
    }

  const QString	credit(_resList.at(1));
  const QString	right(_resList.at(2));
  const QString	status(_resList.at(3));

  qDebug() << "add account" << account;

  QTreeWidgetItem*	item = new QTreeWidgetItem;

  if (!status.toInt())
    item->setIcon(0, QIcon(":/accounts/images/user_gray.png"));
  else if (right.toInt() & (RIGHT_ADMIN | RIGHT_SERVER))
    item->setIcon(0, QIcon(":/accounts/images/user_red.png"));
  else
    item->setIcon(0, QIcon(":/accounts/images/user.png"));

  item->setText(0, account);
  item->setText(1, credit);
  item->setText(2, right);
  item->setText(3, status);

  _client->adminAccountList->addTopLevelItem(item);
}

void	Action::_actAccountsModify()
{
  if (_resList.at(0) == KO)
    {
      QMessageBox::critical(_client,
			    tr("accounts_modify"),
			    tr("accounts_modify_txt"));
      return;
    }

  AccountsAdmin*	aa = AccountsAdmin::getInstance(_client);

  aa->hide();
}

void	Action::_actMessage()
{
  const QString	to(_resList.at(0));

  if (to == KO)
    {
      QMessageBox::critical(_client, tr("message_err"), tr("message_err_txt"));
      return;
    }
  if (to == OK)
    return;

  _client->openMessage(to);

  _resList.erase(_resList.begin());

  _client->appendMessage(to, to, _resList.join(" "));
}

void	Action::_actWeb()
{
  if (_resList.count() < 1)
    return;

  const QString	name(_resList.at(0));

  qDebug() << "add service web" << name;

  _client->serviceWebList->addItem
    (new QListWidgetItem(QIcon(":/services/images/bricks.png"), name));
}

void	Action::_actStream()
{
  if (_resList.count() < 1)
    return;

  const QString	name(_resList.at(0));

  qDebug() << "add service stream" << name;

  _client->serviceStreamList->addItem
    (new QListWidgetItem(QIcon(":/services/images/bricks.png"), name));
}

void	Action::_actWebDetail()
{
  if (_resList.at(0) == KO)
    {
      QMessageBox::critical(_client,
			    tr("web_service_inc"), tr("web_service_inc_txt"));
      return;
    }

  Web*	web = Web::getInstance(_client);

  web->name->setText(_resList.at(0));
  web->space->setText(_resList.at(1));
  web->nbDb->setText(_resList.at(2));
  web->domain->setText(_resList.at(3));

  QDateTime	date;

  date.setTime_t(_resList.at(4).toInt());
  web->created->setText(date.toString());

  date.setTime_t(_resList.at(5).toInt());
  web->expired->setText(date.toString());
}

void	Action::_actStreamDetail()
{
  if (_resList.at(0) == KO)
    {
      QMessageBox::critical(_client,
			    tr("stream_service_inc"),
			    tr("stream_service_inc_txt"));
      return;
    }

  Stream*	stream = Stream::getInstance(_client);

  stream->name->setText(_resList.at(0));
  stream->slotss->setText(_resList.at(1));
  stream->bits->setText(_resList.at(2));
  stream->title->setText(_resList.at(3));
  stream->port->setText(_resList.at(4));

  QDateTime	date;

  date.setTime_t(_resList.at(6).toInt());
  stream->created->setText(date.toString());

  date.setTime_t(_resList.at(7).toInt());
  stream->expired->setText(date.toString());

  QString	status(_resList.at(5));

  if (status == "1")
    {
      stream->start->setEnabled(false);
      stream->stop->setEnabled(true);
    }
  else
    {
      stream->start->setEnabled(true);
      stream->stop->setEnabled(false);
    }
}

void	Action::_actOfferWeb()
{
  if (_resList.count() < 1)
    return;

  const QString	name(_resList.at(0));
  const QString	price(_resList.at(1));

  QListWidgetItem*	item = new QListWidgetItem;

  qDebug() << "add offer web" << name;

  item->setIcon(QIcon(":/services/images/bricks.png"));
  item->setText(name);
  item->setData(Qt::UserRole, price);

  Service::getInstance(_client)->offerWebList->addItem(item);
}

void	Action::_actOfferStream()
{
  if (_resList.count() < 1)
    return;

  const QString	name(_resList.at(0));
  const QString	price(_resList.at(1));

  QListWidgetItem*	item = new QListWidgetItem;

  qDebug() << "add offer stream" << name;

  item->setIcon(QIcon(":/services/images/bricks.png"));
  item->setText(name);
  item->setData(Qt::UserRole, price);
  Service::getInstance(_client)->offerStreamList->addItem(item);
}

void	Action::_actCreateOfferWeb()
{
  if (_resList.at(0) == KO)
    {
      QMessageBox::critical(_client,
			    tr("create_offer_web_err"),
			    tr("create_offer_web_err_txt"));
      return;
    }

  _actCredit();

  QMessageBox::information(_client,
			   tr("create_offer_web"),
			   tr("create_offer_web_txt"));

  _client->addHistory(Client::TYPE_WEB, tr("history_create_offer_web"),
		      (int)time(0));

  Service::getInstance(_client)->hide();
}

void	Action::_actCreateOfferStream()
{
  if (_resList.at(0) == KO)
    {
      QMessageBox::critical(_client,
			    tr("create_offer_stream_err"),
			    tr("create_offer_stream_err_txt"));
      return;
    }

  _actCredit();

  QMessageBox::information(_client,
			   tr("create_offer_stream"),
			   tr("create_offer_stream_txt"));

  _client->addHistory(Client::TYPE_STREAM, tr("history_create_offer_stream"),
		      (int)time(0));

  Service::getInstance(_client)->hide();
}

void	Action::_actCreateWeb()
{
  if (_resList.at(0) == KO)
    {
      QMessageBox::critical(_client,
			    tr("create_web_err"), tr("create_web_err_txt"));
      return;
    }

  _actCredit();

  QMessageBox::information(_client, tr("create_web"), tr("create_web_txt"));

  _client->addHistory(Client::TYPE_WEB, tr("history_create_web"),
		      (int)time(0));

  Service::getInstance(_client)->hide();
}

void	Action::_actCreateStream()
{
  if (_resList.at(0) == KO)
    {
      QMessageBox::critical(_client,
			    tr("create_stream_err"),
			    tr("create_stream_err_txt"));
      return;
    }

  _actCredit();

  QMessageBox::information(_client,
			   tr("create_stream"), tr("create_stream_txt"));

  _client->addHistory(Client::TYPE_STREAM, tr("history_create_stream"),
		      (int)time(0));

  Service::getInstance(_client)->hide();
}

void	Action::_actRenewWeb()
{
  if (_resList.at(0) == KO)
    {
      QMessageBox::critical(_client,
			    tr("renew_web_err"),
			    tr("renew_web_err_txt"));
      return;
    }

  _actCredit();

  QMessageBox::information(_client, tr("renew_web"), tr("renew_web_txt"));

  _client->showServiceSelected();
}

void	Action::_actRenewStream()
{
  if (_resList.at(0) == KO)
    {
      QMessageBox::critical(_client,
			    tr("renew_stream_err"),
			    tr("renew_stream_err_txt"));
      return;
    }

  _actCredit();

  QMessageBox::information(_client,
			   tr("renew_stream"),
			   tr("renew_stream_txt"));

  _client->showServiceSelected();
}

void	Action::_actNews()
{
  if (_resList.count() < 2)
    return;

  const QString	id(_resList.at(0));
  const QString	author(_resList.at(1));
  QDateTime	date;

  date.setTime_t(_resList.at(2).toInt());

  _resList.erase(_resList.begin());
  _resList.erase(_resList.begin());
  _resList.erase(_resList.begin());

  const QString	subject = _resList.join(" ");

  qDebug() << "add news" << subject << date;

  QTreeWidgetItem*	item = new QTreeWidgetItem;

  item->setIcon(0, QIcon(":/news/images/newspaper.png"));

  item->setData(0, Qt::UserRole, id);

  item->setText(0, subject);
  item->setText(1, author);
  item->setText(2, date.toString());

  _client->newsList->addTopLevelItem(item);
}

void	Action::_actNewsDetail()
{
  if (_resList.at(0) == KO)
    return;

  News*	news = News::getInstance(_client);

  news->newsBox->setCurrentIndex(0);

  news->readBody->setText(_resList.join(" "));
  news->readSubject->setText(_client->newsList->currentItem()->text(0));
  news->readAuthor->setText(_client->newsList->currentItem()->text(1));
  news->readDate->setText(_client->newsList->currentItem()->text(2));

  news->show();
}

void	Action::_actNewsAdd()
{
  if (_resList.at(0) == KO)
    {
      QMessageBox::critical(_client,
			    tr("news_add_err"),
			    tr("news_add_err_txt"));
      return;
    }

  QMessageBox::information(_client,
			   tr("news_add"),
			   tr("news_add_txt"));

  News*	news = News::getInstance(_client);

  news->hide();
}

void	Action::_actNewsDelete()
{
  if (_resList.at(0) == KO)
    {
      QMessageBox::critical(_client,
			    tr("news_delete_err"),
			    tr("news_delete_err_txt"));
      return;
    }
}

void	Action::_actStreamStatus()
{
  if (_resList.at(0) != KO)
    {
      Stream*	stream = Stream::getInstance(_client);

      stream->start->setEnabled(false);
      stream->stop->setEnabled(true);
    }
}

void	Action::_actStreamStart()
{
  _actStreamStatus();
}

void	Action::_actStreamStop()
{
  if (_resList.at(0) != KO)
    {
      Stream*	stream = Stream::getInstance(_client);

      stream->start->setEnabled(true);
      stream->stop->setEnabled(false);
    }
}

void	Action::_actHalt()
{
  if (_resList.at(0) == KO)
    {
      QMessageBox::critical(_client, tr("halt_err"), tr("halt_err_txt"));
      return;
    }

  QMessageBox::information(_client, tr("halt_info"), tr("halt_info_txt"));
}

void	Action::_actReload()
{
  if (_resList.at(0) == KO)
    {
      QMessageBox::critical(_client, tr("reload_err"), tr("reload_err_txt"));
      return;
    }

  QMessageBox::information(_client, tr("reload_info"), tr("reload_info_txt"));
}

void	Action::_actPlay()
{
  if (_resList.at(0) == KO)
    {
      QMessageBox::critical(_client, tr("play_err"), tr("play_err_txt"));
      return;
    }

  QMessageBox::information(_client, tr("play_info"), tr("play_info_txt"));
}

void	Action::_actBreak()
{
  if (_resList.at(0) == KO)
    {
      QMessageBox::critical(_client, tr("break_err"), tr("break_err_txt"));
      return;
    }

  QMessageBox::information(_client, tr("break_info"), tr("break_info_txt"));
}

// 
// Action.cpp ends here
