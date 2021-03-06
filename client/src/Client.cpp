// Client.cpp --- 
// 
// Filename: Client.cpp
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 00:43:31 2008 (+0200)
// Version: 
// Last-Updated: Tue Dec  9 12:34:04 2008 (+0200)
//           By: Caner Candan
//     Update #: 189
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

#include <QMessageBox>
#include <QTextStream>
#include <QTime>
#include "Client.h"
#include "Connect.h"
#include "Create.h"
#include "State.h"
#include "Service.h"
#include "Web.h"
#include "Stream.h"
#include "Credit.h"
#include "Options.h"
#include "Database.h"
#include "Socket.h"
#include "Accounts.h"
#include "Protocole.h"
#include "About.h"
#include "Action.h"
#include "News.h"
#include "AccountsAdmin.h"

Client::Client(QWidget *parent /*= NULL*/)
  : QMainWindow(parent)
{
  setupUi(this);

  actionSignUp->setEnabled(false);
  actionSignIn->setEnabled(false);
  actionSignOut->setEnabled(false);

  pageBox->setEnabled(false);
  pageBox->setCurrentIndex(0);

  connect(this, SIGNAL(destroyed(QObject*)),
	  this, SLOT(_beforeClose(QObject*)));

  Socket*	socket = Socket::getInstance();

  connect(socket->socket(), SIGNAL(connected()),
	  this, SLOT(_connectedToServer()));
  connect(socket->socket(), SIGNAL(readyRead()),
	  this, SLOT(_readAction()));
  connect(socket->socket(), SIGNAL(bytesWritten(qint64)),
	  this, SLOT(_sendAction()));
  connect(socket->socket(), SIGNAL(error(QAbstractSocket::SocketError)),
	  this, SLOT(_displayError(QAbstractSocket::SocketError)));

  connect(pageBox, SIGNAL(currentChanged(int)),
	  this, SLOT(_loadPages(int)));
  connect(serviceBox, SIGNAL(currentChanged(int)),
	  this, SLOT(_loadServices(int)));
  connect(creditBox, SIGNAL(currentChanged(int)),
	  this, SLOT(_loadHistory(int)));
  connect(adminBox, SIGNAL(currentChanged(int)),
	  this, SLOT(_loadAdmin(int)));

  Credit*	credit = Credit::getInstance(this);

  connect(creditCurrently, SIGNAL(textChanged(const QString&)),
	  credit->currently, SLOT(setText(const QString&)));
  connect(serviceCredit, SIGNAL(clicked()),
	  credit, SLOT(show()));

  Options*	options = Options::getInstance(this);
  Accounts*	accounts = Accounts::getInstance(this);
  About*	about = About::getInstance(this);

  connect(actionQuit, SIGNAL(triggered()),
	  this, SLOT(close()));
  connect(actionOptions, SIGNAL(triggered()),
	  options, SLOT(show()));
  connect(actionAccounts, SIGNAL(triggered()),
	  accounts, SLOT(show()));
  connect(actionAbout, SIGNAL(triggered()),
	  about, SLOT(show()));

  _loadOptions();
}

Client::~Client()
{
  _saveKey("sizeX", QVariant(this->width()));
  _saveKey("sizeY", QVariant(this->height()));

  _saveKey("posX", QVariant(this->x()));
  _saveKey("posY", QVariant(this->y()));

  Socket::kill();
  Database::kill();
  News::kill();
  Service::kill();
  Web::kill();
  Stream::kill();
  Credit::kill();
  State::kill();
  AccountsAdmin::kill();
  About::kill();

  destroyMessages();
}

void	Client::_beforeClose(QObject*)
{
  qDebug() << __FUNCTION__;
}

void	Client::_loadOptions()
{
  if (_keyExist("sizeX") && _keyExist("sizeY"))
    {
      int	x = _getKeyValue("sizeX").toInt();
      int	y = _getKeyValue("sizeY").toInt();

      this->resize(x, y);
    }

  if (_keyExist("posX") && _keyExist("posY"))
    {
      int	x = _getKeyValue("posX").toInt();
      int	y = _getKeyValue("posY").toInt();

      this->move(x, y);
    }

  if (_keyExist("mask"))
    {
      QVariant	value = _getKeyValue("mask");

      if (value.toInt() & OPT_SPLASH)
	{
	  QSqlQuery	q(Database::getInstance()->database());

	  q.prepare("select username from users;");
	  q.exec();

	  if (q.next())
	    this->on_actionSignIn_triggered();
	  else
	    this->on_actionSignUp_triggered();
	}
    }
}

QVariant	Client::_getKeyValue(const QString& key)
{
  QSqlQuery	q(Database::getInstance()->database());

  q.prepare("select value "
	    "from options "
	    "where key = ?;");
  q.addBindValue(key);
  q.exec();

  if (q.next())
    return (q.value(0));
  return ("");
}

bool	Client::_keyExist(const QString& key)
{
  QSqlQuery	q(Database::getInstance()->database());

  q.prepare("select key "
	    "from options "
	    "where key = ?;");
  q.addBindValue(key);
  q.exec();

  return (q.next());
}

void	Client::_saveKey(const QString& key, const QVariant& value)
{
  QSqlQuery	q(Database::getInstance()->database());

  if (!_keyExist(key))
    {
      q.prepare("insert into options "
		"values(?, ?);");
      q.addBindValue(key);
      q.addBindValue(value.toString());
      q.exec();
    }
  else
    {
      q.prepare("update options "
		"set value = ? "
		"where key = ?;");
      q.addBindValue(value.toString());
      q.addBindValue(key);
      q.exec();
    }
}

void	Client::openMessage(const QString& sName)
{
  if (!_mm.contains(sName) ||
      !_mm[sName])
    _mm[sName] = new Message(this);
  _mm[sName]->from->setText(this->infoAccount->text());
  _mm[sName]->to->setText(sName);
  _mm[sName]->show();
}

void	Client::destroyMessages()
{
  for (MessageMap::iterator
	 it = _mm.begin(),
	 end = _mm.end();
       it != end; ++it)
    {
      if (it.value())
	{
	  it.value()->close();
	  delete it.value();
	}
      _mm[it.key()] = NULL;
    }
}

void	Client::appendMessage(const QString& sName,
			      const QString& from,
			      const QString& body)
{
  const QString	time(QTime::currentTime().toString());
  QTextEdit*	list = _mm[sName]->list;

  list->append('[' + time + "] " + from + "> " + body);
}

void	Client::login()
{
  this->actionSignUp->setEnabled(false);
  this->actionSignIn->setEnabled(false);
  this->actionSignOut->setEnabled(true);
  this->pageBox->setEnabled(true);
  this->infoStatus->setText(tr("online"));
  this->statusbar->showMessage(tr("bar_login"));
  this->_loadPages(0);
}

void	Client::logout()
{
  this->actionSignUp->setEnabled(true);
  this->actionSignIn->setEnabled(true);
  this->actionSignOut->setEnabled(false);
  this->pageBox->setEnabled(false);
  this->infoAccount->setText(tr("guest"));
  this->infoStatus->setText(tr("offline"));
  this->statusbar->showMessage(tr("bar_logout"));
  this->pageBox->setCurrentIndex(0);
  this->destroyMessages();
  this->newsList->clear();
  this->serviceBox->setCurrentIndex(0);
  this->serviceWebList->clear();
  this->serviceStreamList->clear();
  this->talkMyContactsList->clear();
  this->talkAllContactsList->clear();
  this->creditWebList->clear();
  this->creditStreamList->clear();
  this->adminAccountList->clear();

  News::kill();
  Service::kill();
  Web::kill();
  Stream::kill();
  Credit::kill();
  State::kill();
  AccountsAdmin::kill();
}

void	Client::on_actionSignUp_triggered()
{
  Create	create(this);
  QTextStream	stream(Socket::getInstance()->socket());

  if (create.exec() != QDialog::Accepted)
    return;

  _userCreated = create.username->text();

  stream << CREATE << SP << _userCreated << NL;
}

void	Client::on_actionSignIn_triggered()
{
  Connect	connect(this);
  QTextStream	stream(Socket::getInstance()->socket());

  if (connect.exec() != QDialog::Accepted)
    return;

  stream << LOGIN
	 << SP << connect.username->text()
	 << SP << connect.password->text()
	 << NL;

  this->infoAccount->setText(connect.username->text());
}

void	Client::on_actionSignOut_triggered()
{
  QTextStream	stream(Socket::getInstance()->socket());

  stream << LOGOUT << NL;
}

void	Client::loadNews()
{
  bool	rightNews = (this->getRight() & RIGHT_NEWS);
  bool	rightAdmin = (this->getRight() & RIGHT_ADMIN);

  this->newsList->setEnabled(rightNews);
  this->newsRead->setEnabled(rightNews);
  this->newsAdd->setEnabled(rightNews && rightAdmin);
  this->newsDelete->setEnabled(rightNews && rightAdmin);

  if (!rightNews)
    return;

  State*	state = State::getInstance();

  if (state->getNewsList() == State::DONE)
    return;

  QTextStream	stream(Socket::getInstance()->socket());

  stream << NEWS << NL;
}

void	Client::on_serviceAdd_clicked()
{
  Service*	service = Service::getInstance(this);
  int		idx = this->serviceBox->currentIndex();

  this->loadOffers(idx);
  service->serviceBox->setCurrentIndex(idx);

  service->show();
}

void	Client::showServiceSelected()
{
  QTextStream	stream(Socket::getInstance()->socket());

  if (!this->serviceBox->currentIndex())
    {
      if (this->serviceWebList->currentRow() < 0)
	return;

      const QString	name(this->serviceWebList->currentItem()->text());

      if (name.isEmpty())
	return;

      stream << WEB_DETAIL << SP << name << NL;

      Web::getInstance(this)->show();
    }
  else
    {
      if (this->serviceStreamList->currentRow() < 0)
	return;

      const QString	name(this->serviceStreamList->currentItem()->text());

      if (name.isEmpty())
	return;

      stream << STREAM_DETAIL << SP << name << NL;

      Stream::getInstance(this)->show();
    }
}

void	Client::on_serviceManage_clicked()
{
  showServiceSelected();
}

void	Client::on_newsRead_clicked()
{
  if (!this->newsList->currentItem())
    return;

  QTextStream	stream(Socket::getInstance()->socket());

  stream << NEWS_DETAIL << SP
	 << this->newsList->currentItem()->data(0, Qt::UserRole).toString()
	 << NL;
}

void	Client::on_newsAdd_clicked()
{
  News*	news = News::getInstance(this);

  news->newsBox->setCurrentIndex(1);
  news->addSubject->setFocus();
  news->show();
}

void	Client::on_newsDelete_clicked()
{
  if (!this->newsList->currentItem())
    return;

  QTextStream	stream(Socket::getInstance()->socket());

  stream << NEWS_DELETE << SP
	 << this->newsList->currentItem()->data(0, Qt::UserRole).toString()
	 << NL;
}

void	Client::on_talkOpen_clicked()
{
  QString	sName;

  if (!this->talkBox->currentIndex())
    {
      if (this->talkMyContactsList->currentRow() < 0)
	return;
      this->openMessage(this->talkMyContactsList->currentItem()->
			data(Qt::UserRole).toString());
      return;
    }
  if (this->talkAllContactsList->currentRow() < 0)
    return;
  this->openMessage(this->talkAllContactsList->currentItem()->text());
}

void	Client::on_talkMyContactsAdd_clicked()
{
  Contact	contact;

  if (contact.exec() != QDialog::Accepted)
    return;

  this->addToContactsList(contact);
}

void	Client::on_talkMyContactsDel_clicked()
{
  if (this->talkMyContactsList->currentRow() < 0)
    return;

  if (QMessageBox::question(this, tr("are_you_sure"), tr("are_you_sure_txt"),
			    QMessageBox::Yes | QMessageBox::No)
      != QMessageBox::Yes)
    return;

  QSqlQuery	q(Database::getInstance()->database());

  q.prepare("delete from contacts "
	    "where username = ? and contact = ?;");
  q.addBindValue(this->infoAccount->text());
  q.addBindValue(this->talkMyContactsList->currentItem()->data(Qt::UserRole));
  q.exec();

  State::getInstance()->setClientsList(State::WAIT);
  this->loadClients();
}

void	Client::on_talkAllContactsAdd_clicked()
{
  if (this->talkAllContactsList->currentRow() < 0)
    return;

  Contact	contact;

  contact.username->setText(this->talkAllContactsList->currentItem()->text());
  contact.alias->setFocus();

  if (contact.exec() != QDialog::Accepted)
    return;

  this->addToContactsList(contact);
}

void	Client::addToContactsList(const Contact& contact)
{
  QSqlQuery	q(Database::getInstance()->database());

  q.prepare("insert into contacts "
	    "values(null, ?, ?, ?);");
  q.addBindValue(this->infoAccount->text());
  q.addBindValue(contact.username->text());
  q.addBindValue(contact.alias->text());
  q.exec();

  State::getInstance()->setClientsList(State::WAIT);
  this->loadClients();
}

void	Client::on_adminModify_clicked()
{
  if (!this->adminAccountList->currentItem())
    return;

  AccountsAdmin*	aa = AccountsAdmin::getInstance(this);

  aa->account->setText(this->adminAccountList->currentItem()->text(0));
  aa->currentCredit->setText(this->adminAccountList->currentItem()->text(1));
  aa->newCredit->setText(aa->currentCredit->text());

  int	right = this->adminAccountList->currentItem()->text(2).toInt();

  qDebug() << right;

  aa->rightMessage->setChecked((right & RIGHT_MESSAGE) == RIGHT_MESSAGE);
  aa->rightWeb->setChecked((right & RIGHT_WEB) == RIGHT_WEB);
  aa->rightStream->setChecked((right & RIGHT_STREAM) == RIGHT_STREAM);
  aa->rightNews->setChecked((right & RIGHT_NEWS) == RIGHT_NEWS);
  aa->rightServer->setChecked((right & RIGHT_SERVER) == RIGHT_SERVER);
  aa->rightAdmin->setChecked((right & RIGHT_ADMIN) == RIGHT_ADMIN);

  aa->show();
}

void	Client::on_adminCreditAccept_clicked()
{
  if (!_acceptRejectCredit())
    return;

  QTextStream	stream(Socket::getInstance()->socket());
  QString	id(this->adminCreditList->currentItem()->data
		   (0, Qt::UserRole).toString());

  stream << ACCEPT_CREDIT << SP << id << NL;
}

void	Client::on_adminCreditReject_clicked()
{
  if (!_acceptRejectCredit())
    return;

  QTextStream	stream(Socket::getInstance()->socket());
  QString	id(this->adminCreditList->currentItem()->data
		   (0, Qt::UserRole).toString());

  stream << REJECT_CREDIT << SP << id << NL;
}

bool	Client::_acceptRejectCredit()
{
  if (!this->adminCreditList->currentItem())
    return (false);

  if (QMessageBox::question(this, tr("are_you_sure"), tr("are_you_sure_txt"),
			    QMessageBox::Ok | QMessageBox::Cancel)
      != QMessageBox::Ok)
    return (false);

  return (true);
}

void	Client::on_serverHalt_clicked()
{
  QTextStream	stream(Socket::getInstance()->socket());

  stream << HALT << NL;
}

void	Client::on_serverReload_clicked()
{
  QTextStream	stream(Socket::getInstance()->socket());

  stream << RELOAD << NL;
}

void	Client::on_serverPlay_clicked()
{
  QTextStream	stream(Socket::getInstance()->socket());

  stream << PLAY << NL;
}

void	Client::on_serverBreak_clicked()
{
  QTextStream	stream(Socket::getInstance()->socket());

  stream << BREAK << NL;
}

void	Client::_connectedToServer()
{
  this->statusbar->showMessage(tr("bar_connected"));
  this->setEnabled(true);
  this->actionSignUp->setEnabled(true);
  this->actionSignIn->setEnabled(true);
}

void	Client::_readAction()
{
  Action	action(this, _userCreated);

  action.execute();
}

void	Client::_sendAction()
{}

void	Client::_displayError(QAbstractSocket::SocketError)
{
  Options*	options = Options::getInstance(this);

  QMessageBox::critical(this, tr("not_connected"),
			tr("not_connected_txt"));
  this->logout();
  this->setEnabled(false);
  options->setEnabled(true);
  options->show();
}

void	Client::loadOffers(int idx)
{
  if ((idx == 0 && !(this->getRight() & RIGHT_WEB)) ||
      (idx == 1 && !(this->getRight() & RIGHT_STREAM)))
    return;

  QTextStream	stream(Socket::getInstance()->socket());
  State*	state = State::getInstance();

  if (idx == 0)
    {
      if (state->getOfferWebList() == State::DONE)
	return;

      stream << OFFER_WEB << NL;

      return;
    }

  if (state->getOfferStreamList() == State::DONE)
    return;

  stream << OFFER_STREAM << NL;
}

void	Client::_loadPages(int idx)
{
  QTextStream	stream(Socket::getInstance()->socket());

  if (idx == 0) // news
    this->loadNews();
  else if (idx == 1) // services
    this->_loadServices(0);
  else if (idx == 2) // credit
    this->_loadHistory(0);
  else if (idx == 3) // talk
    this->loadClients();
  else if (idx == 4) // admin
    this->_loadAdmin(0);
}

void	Client::_loadServices(int idx)
{
  bool	rightAll = (this->getRight() & (RIGHT_WEB | RIGHT_STREAM));
  bool	rightWeb = (this->getRight() & RIGHT_WEB);
  bool	rightStream = (this->getRight() & RIGHT_STREAM);

  this->serviceWebList->setEnabled(rightWeb);
  this->serviceStreamList->setEnabled(rightStream);
  this->serviceManage->setEnabled(rightAll);
  this->serviceAdd->setEnabled(rightAll);

  if ((idx == 0 && !rightWeb) ||
      (idx == 1 && !rightStream))
    return;

  QTextStream	stream(Socket::getInstance()->socket());
  State*	state = State::getInstance();

  if (idx == 0)
    {
      if (state->getWebList() == State::DONE)
	return;

      stream << WEB << NL;

      return;
    }

  if (state->getStreamList() == State::DONE)
    return;

  stream << STREAM << NL;
}

void	Client::loadClients()
{
  bool	right = (this->getRight() & RIGHT_MESSAGE);

  this->talkBox->setEnabled(right);
  this->talkOpen->setEnabled(right);

  if (!right)
    return;

  State*	state = State::getInstance();

  if (state->getClientsList() == State::DONE)
    return;

  QTextStream	stream(Socket::getInstance()->socket());

  stream << CLIENTS << NL;
}

void	Client::loadMyContact(const QString& contact,
			      const int& right)
{
  QSqlQuery	q(Database::getInstance()->database());

  q.prepare("select alias "
	    "from contacts "
	    "where username = ? and contact = ?;");
  q.addBindValue(this->infoAccount->text());
  q.addBindValue(contact);
  q.exec();
  if (!q.next())
    return;

  QListWidgetItem*	item = new QListWidgetItem;

  if (right & (RIGHT_ADMIN | RIGHT_SERVER))
    item->setIcon(QIcon(":/talk/images/user_red.png"));
  else
    item->setIcon(QIcon(":/talk/images/user.png"));

  if (q.value(0).toString().isEmpty())
    item->setText(contact);
  else
    item->setText(q.value(0).toString() + " <" + contact + ">");
  item->setData(Qt::UserRole, contact);
  this->talkMyContactsList->addItem(item);
}

void	Client::loadAllContact(const QString& contact,
			       const int& right)
{
  QListWidgetItem*	item = new QListWidgetItem;

  if (right & (RIGHT_ADMIN | RIGHT_SERVER))
    item->setIcon(QIcon(":/talk/images/user_red.png"));
  else
    item->setIcon(QIcon(":/talk/images/user.png"));

  item->setText(contact);

  this->talkAllContactsList->addItem(item);
}

void	Client::_loadAdmin(int idx)
{
  bool	rightAdmin = ((this->getRight() & RIGHT_ADMIN) == RIGHT_ADMIN);
  bool	rightServer = ((this->getRight() & RIGHT_SERVER) == RIGHT_SERVER);

  this->adminBox->setEnabled(rightAdmin || rightServer);

  QTextStream	stream(Socket::getInstance()->socket());
  State*	state = State::getInstance();

  if (idx == 0)
    {
      this->adminAccountList->setEnabled(rightAdmin);
      this->adminModify->setEnabled(rightAdmin);

      if (!rightAdmin)
	return;

      if (state->getAccountsList() == State::DONE)
	return;

      stream << ACCOUNTS << NL;
    }
  else if (idx == 1)
    {
      this->adminCreditList->setEnabled(rightAdmin);
      this->adminCreditAccept->setEnabled(rightAdmin);
      this->adminCreditReject->setEnabled(rightAdmin);

      if (!rightAdmin)
	return;

      if (state->getCreditList() == State::DONE)
	return;

      stream << LIST_CREDIT << NL;
    }
  else if (idx == 2)
    {
      this->serverHalt->setEnabled(rightServer);
      this->serverReload->setEnabled(rightServer);
      this->serverPlay->setEnabled(rightServer);
      this->serverBreak->setEnabled(rightServer);
    }
}

void	Client::_loadHistory(int idx)
{
  QSqlQuery	q(Database::getInstance()->database());
  QListWidget*	list;
  ServiceType	type;

  q.prepare("select describe, date "
	    "from history "
	    "where username = ? and type = ? "
	    "order by date desc;");
  if (!idx) // web
    {
      type = TYPE_WEB;
      list = this->creditWebList;
    }
  else // stream
    {
      type = TYPE_STREAM;
      list = this->creditStreamList;
    }
  q.addBindValue(this->infoAccount->text());
  q.addBindValue(type);
  q.exec();
  list->clear();
  while (q.next())
    list->addItem(new QListWidgetItem
		  (QIcon(":/credit/images/bricks.png"),
		   q.value(0).toString()));
}

void	Client::addHistory(const Client::ServiceType& type,
			   const QString& describe,
			   const int& price)
{
  QSqlQuery	q(Database::getInstance()->database());

  q.prepare("insert into history values(null, ?, ?, ?, ?, ?);");
  q.addBindValue(this->infoAccount->text());
  q.addBindValue(type);
  q.addBindValue(describe);
  q.addBindValue(price);
  q.addBindValue(-1);
  q.exec();
}

int	Client::getCredit() const
{
  return (this->creditCurrently->text().toInt());
}

void	Client::setCredit(const int& credit)
{
  this->creditCurrently->setText(QVariant(credit).toString());
}

// 
// Client.cpp ends here
