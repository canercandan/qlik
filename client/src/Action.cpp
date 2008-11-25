//
// Action.cpp for client in /home/candan_c/cu/rendu/qlik/client/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Thu Oct 30 14:59:45 2008 caner candan
// Last update Tue Nov 25 13:51:46 2008 caner candan
//

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

	  pairCallback	pairCallback = _mapAction[action];
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
	  action = resList.at(0);

	  if (action == BEGIN)
	    {
	      qDebug() << "i start";
	      resList.erase(resList.begin());
	      func = callback;
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

  _actCredit();

  _resList.erase(_resList.begin());
  _actRight();

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

  _client->setCredit(_resList.at(0).toInt());
}

void	Action::_actStatus()
{}

void	Action::_actRight()
{
  if (_resList.at(0) == KO)
    return;

  _client->setRight(_resList.at(0).toInt());
}

void	Action::_actClients()
{
  if (_resList.count() < 1)
    return;

  const QString	name(_resList.at(0));
  const int	right(_resList.at(1).toInt());

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
    item->setIcon(0, QIcon("../images/user_gray.png"));
  else if (right.toInt() & (RIGHT_ADMIN | RIGHT_SERVER))
    item->setIcon(0, QIcon("../images/user_red.png"));
  else
    item->setIcon(0, QIcon("../images/user.png"));

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

  _client->refreshList();

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

  _client->serviceWebList->addItem(new QListWidgetItem
				   (QIcon("../images/bricks.png"), name));
}

void	Action::_actStream()
{
  if (_resList.count() < 1)
    return;

  const QString	name(_resList.at(0));

  qDebug() << "add service stream" << name;

  _client->serviceStreamList->addItem(new QListWidgetItem
				      (QIcon("../images/bricks.png"), name));
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

  item->setIcon(QIcon("../images/bricks.png"));
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

  item->setIcon(QIcon("../images/bricks.png"));
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

  Service*	service =   Service::getInstance(_client);

  QMessageBox::information(_client,
			   tr("create_offer_web"),
			   tr("create_offer_web_txt"));

  _client->subCredit(service->offerWebList->currentItem()->
		     data(Qt::UserRole).toInt());
  _client->addHistory(Client::TYPE_WEB, tr("history_create_offer_web"), -1);

  State::getInstance()->setWebList(State::WAIT);

  _client->refreshList();

  service->hide();
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

  Service*	service =   Service::getInstance(_client);

  QMessageBox::information(_client,
			   tr("create_offer_stream"),
			   tr("create_offer_stream_txt"));

  _client->subCredit(service->offerStreamList->currentItem()->
		     data(Qt::UserRole).toInt());
  _client->addHistory(Client::TYPE_STREAM, tr("history_create_offer_stream"), -1);
  State::getInstance()->setStreamList(State::WAIT);

  _client->refreshList();

  service->hide();
}

void	Action::_actCreateWeb()
{
  if (_resList.at(0) == KO)
    {
      QMessageBox::critical(_client,
			    tr("create_web_err"), tr("create_web_err_txt"));
      return;
    }

  Service*	service = Service::getInstance(_client);

  QMessageBox::information(_client, tr("create_web"), tr("create_web_txt"));

  _client->subCredit
    ((service->webSpace->currentText().toInt() / RATIO_WEB_SPACE)
     + (service->webNbDb->currentText().toInt() / RATIO_WEB_DB));

  _client->addHistory(Client::TYPE_WEB, tr("history_create_web"), -1);

  State::getInstance()->setWebList(State::WAIT);

  _client->refreshList();

  service->hide();
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

  Service*	service = Service::getInstance(_client);

  QMessageBox::information(_client,
			   tr("create_stream"), tr("create_stream_txt"));
  _client->subCredit
    ((service->streamSlots->currentText().toInt() / RATIO_STREAM_SLOT)
     + (service->streamBits->currentText().toInt() / RATIO_STREAM_BITS));

  _client->addHistory(Client::TYPE_STREAM, tr("history_create_stream"), -1);

  State::getInstance()->setStreamList(State::WAIT);

  _client->refreshList();

  service->hide();
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

  item->setIcon(0, QIcon("../images/newspaper.png"));

  item->setData(0, Qt::UserRole, id);

  item->setText(0, subject);
  item->setText(1, author);
  item->setText(2, date.toString());

  _client->newsList->addTopLevelItem(item);

  _client->actionRefresh->setEnabled(true);
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

  _client->refreshList();
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

  _client->refreshList();
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
