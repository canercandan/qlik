//
// Action.cpp for client in /home/candan_c/cu/rendu/qlik/client/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Thu Oct 30 14:59:45 2008 caner candan
// Last update Thu Oct 30 16:23:57 2008 caner candan
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
	  if (_mapAction.find(resList.at(0)) == _mapAction.end())
	    return;

	  callback	callback = _mapAction[action];

	  qDebug() << "action found" << action;

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
  _mapAction[WELCOME] = &Action::_actWelcome;

  _mapAction[LOGIN] = &Action::_actLogin;
  _mapAction[LOGOUT] = &Action::_actLogout;
  _mapAction[CREATE] = &Action::_actCreate;

  _mapAction[CREDIT] = &Action::_actCredit;

  _mapAction[STATUS] = &Action::_actStatus;

  _mapAction[CLIENTS] = &Action::_actClients;
  _mapAction[ACCOUNTS] = &Action::_actAccounts;
  _mapAction[MESSAGE] = &Action::_actMessage;

  _mapAction[WEB] = &Action::_actWeb;
  _mapAction[STREAM] = &Action::_actStream;

  _mapAction[WEB_DETAIL] = &Action::_actWebDetail;
  _mapAction[STREAM_DETAIL] = &Action::_actStreamDetail;

  _mapAction[OFFER_WEB] = &Action::_actOfferWeb;
  _mapAction[OFFER_STREAM] = &Action::_actOfferStream;

  _mapAction[CREATE_OFFER_WEB] = &Action::_actCreateOfferWeb;
  _mapAction[CREATE_OFFER_STREAM] = &Action::_actCreateOfferStream;
  _mapAction[CREATE_WEB] = &Action::_actCreateWeb;
  _mapAction[CREATE_STREAM] = &Action::_actCreateStream;

  _mapAction[NEWS] = &Action::_actNews;
  _mapAction[NEWS_DETAIL] = &Action::_actNewsDetail;

  _mapAction[STREAM_STATUS] = &Action::_actStreamStatus;
  _mapAction[STREAM_START] = &Action::_actStreamStart;
  _mapAction[STREAM_STOP] = &Action::_actStreamStop;
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

void	Action::_actClients()
{
  if (_resList.count() < 1)
    return;

  const QString	name(_resList.at(0));

  if (name == _client->infoAccount->text())
    return;

  qDebug() << "add client" << name;

  _client->loadAllContact(name);
  _client->loadMyContact(name);
}

void	Action::_actAccounts()
{}

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

  QStringList	resMessage(_resList);

  resMessage.erase(resMessage.begin());
  _client->appendMessage(to, to, resMessage.join(" "));
}

void	Action::_actWeb()
{
  if (_resList.count() < 1)
    return;

  const QString	name(_resList.at(0));

  qDebug() << "add service web" << name;

  _client->serviceWebList->addItem(new QListWidgetItem
				   (QIcon("images/bricks.png"), name));
}

void	Action::_actStream()
{
  if (_resList.count() < 1)
    return;

  const QString	name(_resList.at(0));

  qDebug() << "add service stream" << name;

  _client->serviceStreamList->addItem(new QListWidgetItem
				      (QIcon("images/bricks.png"), name));
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

  const QString	price(_resList.at(0));
  const QString	name(_resList.at(1));

  QListWidgetItem*	item = new QListWidgetItem;

  qDebug() << "add offer web" << name;

  item->setIcon(QIcon("images/bricks.png"));
  item->setText(name);
  item->setData(Qt::UserRole, price);
  Service::getInstance(_client)->offerWebList->addItem(item);
}

void	Action::_actOfferStream()
{
  if (_resList.count() < 1)
    return;

  const QString	price(_resList.at(0));
  const QString	name(_resList.at(1));

  QListWidgetItem*	item = new QListWidgetItem;

  qDebug() << "add offer stream" << name;

  item->setIcon(QIcon("images/bricks.png"));
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
  const int	date = _resList.at(1).toInt();
  const QString	sDate(::ctime((time_t*)&date));

  QStringList	resMessage(_resList);

  resMessage.erase(resMessage.begin());
  resMessage.erase(resMessage.begin());

  const QString	subject = resMessage.join(" ");

  qDebug() << "add news" << subject << date;
  qDebug() << sDate;

  QListWidgetItem*	item = new QListWidgetItem;

  //item->setIcon(QIcon("images/bricks.png"));
  item->setText(sDate + ' ' + subject);
  item->setData(Qt::UserRole, id);

  _client->newsList->addItem(item);

  _client->actionRefresh->setEnabled(true);
}

void	Action::_actNewsDetail()
{
  if (_resList.at(0) != KO)
    QMessageBox::information(_client, tr("news_box"),
			     _resList.join(" "));
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
