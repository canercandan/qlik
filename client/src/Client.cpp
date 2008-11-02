//
// Client.cpp for Client in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Jul 15 15:29:04 2008 caner candan
// Last update Sun Nov  2 12:33:04 2008 caner candan
//

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

Client::Client(QWidget *parent /*= NULL*/)
  : QMainWindow(parent), _credit(0)
{
  Socket*	socket = Socket::getInstance();

  setupUi(this);

  actionSignUp->setEnabled(false);
  actionSignIn->setEnabled(false);
  actionSignOut->setEnabled(false);
  actionRefresh->setEnabled(false);

  pageBox->setEnabled(false);
  pageBox->setCurrentIndex(0);

  connect(socket->socket(), SIGNAL(connected()),
	  this, SLOT(connectedToServer()));
  connect(socket->socket(), SIGNAL(readyRead()),
	  this, SLOT(readAction()));
  connect(socket->socket(), SIGNAL(bytesWritten(qint64)),
	  this, SLOT(sendAction()));
  connect(socket->socket(), SIGNAL(error(QAbstractSocket::SocketError)),
	  this, SLOT(displayError(QAbstractSocket::SocketError)));
  connect(pageBox, SIGNAL(currentChanged(int)),
	  this, SLOT(loadPages(int)));
  connect(serviceBox, SIGNAL(currentChanged(int)),
	  this, SLOT(loadServices(int)));
  connect(creditBox, SIGNAL(currentChanged(int)),
	  this, SLOT(loadHistory(int)));

  Options::getInstance(this);

  if (_keyExist("sizeX") && _keyExist("sizeY"))
    {
      int	x = _getKeyValue("sizeX").toInt();
      int	y = _getKeyValue("sizeY").toInt();

      resize(x, y);
    }

  if (_keyExist("posX") && _keyExist("posY"))
    {
      int	x = _getKeyValue("posX").toInt();
      int	y = _getKeyValue("posY").toInt();

      move(x, y);
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
	    on_actionSignIn_triggered();
	  else
	    on_actionSignUp_triggered();
	}
    }
}

Client::~Client()
{
  _saveKey("sizeX", QVariant(this->width()));
  _saveKey("sizeY", QVariant(this->height()));

  _saveKey("posX", QVariant(this->x()));
  _saveKey("posY", QVariant(this->y()));

  Socket::kill();
  Database::kill();
  Service::kill();
  Web::kill();
  Stream::kill();
  Credit::kill();

  destroyMessages();
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
  QTextEdit*	list = this->_mm[sName]->list;

  list->append('[' + time + "] " + from + "> " + body);
}

void	Client::login()
{
  this->actionSignUp->setEnabled(false);
  this->actionSignIn->setEnabled(false);
  this->actionSignOut->setEnabled(true);
  this->actionRefresh->setEnabled(true);
  this->pageBox->setEnabled(true);
  this->infoStatus->setText(tr("online"));
  this->statusbar->showMessage(tr("bar_login"));
  this->on_actionRefresh_triggered();
}

void	Client::logout()
{
  this->actionSignUp->setEnabled(true);
  this->actionSignIn->setEnabled(true);
  this->actionSignOut->setEnabled(false);
  this->actionRefresh->setEnabled(false);
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
  this->talkAllContactsList->clear();
  if (Service::exist())
    {
      Service*	service = Service::getInstance(this);

      service->offerWebList->clear();
      service->offerStreamList->clear();
    }
  State::getInstance()->reset();
}

void	Client::on_actionSignUp_triggered()
{
  Create	create(this);
  QTextStream	stream(Socket::getInstance()->socket());

  if (create.exec() != QDialog::Accepted)
    return;
  _userCreated = create.username->text();
  stream << CREATE
	 << ' ' << this->_userCreated
	 << endl;
}

void	Client::on_actionSignIn_triggered()
{
  Connect	connect(this);
  QTextStream	stream(Socket::getInstance()->socket());

  if (connect.exec() != QDialog::Accepted)
    return;
  stream << LOGIN
	 << ' ' << connect.username->text()
	 << ' ' << connect.password->text()
	 << endl;
  this->infoAccount->setText(connect.username->text());
}

void	Client::on_actionSignOut_triggered()
{
  QTextStream	stream(Socket::getInstance()->socket());

  stream << LOGOUT << endl;
}

void	Client::on_actionRefresh_triggered()
{
  this->refreshList();
}

void	Client::refreshList()
{
  QTextStream	stream(Socket::getInstance()->socket());
  int		idx;

  idx = this->pageBox->currentIndex();
  if (!idx) // news
    {
      this->newsList->clear();
      stream << NEWS << endl;
      this->actionRefresh->setEnabled(false);
    }
  else if (idx == 1) // services
    {
      if (!this->serviceBox->currentIndex()) // web
	this->loadServices(0);
      else // stream
	this->loadServices(1);
    }
  else if (idx == 2) // credit
    {
      if (!this->creditBox->currentIndex()) // web
	this->loadHistory(0);
      else // stream
	this->loadHistory(1);
    }
  else if (idx == 3) // talk
    this->loadClients();
}

void	Client::on_actionAbout_triggered()
{
  About	about(this);

  about.exec();
}

void	Client::on_actionQuit_triggered()
{
  this->close();
}

void	Client::on_actionOptions_triggered()
{
  Options::getInstance()->show();
}

void	Client::on_actionAccounts_triggered()
{
  Accounts::getInstance()->show();
}

void	Client::on_serviceAdd_clicked()
{
  Service*	service = Service::getInstance(this);

  connect(service->serviceBox, SIGNAL(currentChanged(int)),
	  this, SLOT(loadOffers(int)));
  if (!this->serviceBox->currentIndex())
    {
      this->loadOffers(0);
      service->serviceBox->setCurrentIndex(0);
    }
  else
    {
      this->loadOffers(1);
      service->serviceBox->setCurrentIndex(1);
    }
  service->show();
}

void	Client::on_serviceManage_clicked()
{
  QTextStream	stream(Socket::getInstance()->socket());

  if (!this->serviceBox->currentIndex())
    {
      const QString	name(this->serviceWebList->currentItem()->text());

      if (name.isEmpty())
	return;

      stream << WEB_DETAIL
	     << ' ' << name
	     << endl;

      Web::getInstance(this)->show();
    }
  else
    {
      const QString	name(this->serviceStreamList->currentItem()->text());

      if (name.isEmpty())
	return;

      stream << STREAM_DETAIL
	     << ' ' << name
	     << endl;

      Stream::getInstance(this)->show();
    }
}

void	Client::on_serviceCredit_clicked()
{
  Credit::getInstance(this)->show();
}

void	Client::on_newsRead_clicked()
{
  QTextStream	stream(Socket::getInstance()->socket());

  if (this->newsList->currentRow() >= 0)
    stream << NEWS_DETAIL
	   << ' ' << this->newsList->currentItem()->data(Qt::UserRole)
	   << endl;
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
  this->loadClients();
}

void	Client::connectedToServer()
{
  this->statusbar->showMessage(tr("bar_connected"));
  this->setEnabled(true);
  this->actionSignUp->setEnabled(true);
  this->actionSignIn->setEnabled(true);
}

void	Client::readAction()
{
  Action	action(this, _userCreated);

  action.execute();
}

void	Client::sendAction()
{}

void	Client::displayError(QAbstractSocket::SocketError)
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
  QTextStream	stream(Socket::getInstance()->socket());
  Service*	service = Service::getInstance(this);

  if (!idx)
    {
      if (service->offerWebList->count())
	return;
      stream << OFFER_WEB << endl;
      return;
    }
  if (service->offerStreamList->count())
    return;
  stream << OFFER_STREAM << endl;
}

void	Client::loadPages(int idx)
{
  QTextStream	stream(Socket::getInstance()->socket());

  if (idx == 1) // services
    this->loadServices(0);
  else if (idx == 2) // credit
    this->loadHistory(0);
  else if (idx == 3) // talk
    this->loadClients();
}

void	Client::loadServices(int idx)
{
  QTextStream	stream(Socket::getInstance()->socket());
  State*	state = State::getInstance();

  if (!idx)
    {
      if (state->getWebList() == State::DONE)
	return;
      this->serviceWebList->clear();
      stream << WEB << endl;
      state->setWebList(State::DONE);
      return;
    }
  if (state->getStreamList() == State::DONE)
    return;
  this->serviceStreamList->clear();
  stream << STREAM << endl;
  state->setStreamList(State::DONE);
}

void	Client::loadClients()
{
  QTextStream	stream(Socket::getInstance()->socket());

  this->talkAllContactsList->clear();
  this->talkMyContactsList->clear();
  stream << CLIENTS << endl;
}

void	Client::loadMyContact(const QString& contact)
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

  item->setIcon(QIcon("images/user.png"));
  if (q.value(0).toString().isEmpty())
    item->setText(contact);
  else
    item->setText(q.value(0).toString() + " <" + contact + ">");
  item->setData(Qt::UserRole, contact);
  this->talkMyContactsList->addItem(item);
}

void	Client::loadAllContact(const QString& contact)
{
  QListWidgetItem*	item = new QListWidgetItem;

  item->setIcon(QIcon("images/user.png"));
  item->setText(contact);
  this->talkAllContactsList->addItem(item);
}

void	Client::loadHistory(int idx)
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
		  (QIcon("images/bricks.png"),
		   q.value(0).toString()));
}

void	Client::createOfferWeb()
{
  QTextStream	stream(Socket::getInstance()->socket());
  Service*	service = Service::getInstance(this);

  stream << CREATE_OFFER_WEB
	 << ' ' << service->offerWebName->text()
	 << ' ' << service->offerWebList->currentRow()
	 << ' ' << service->offerWebDomain->text()
	 << endl;
}

void	Client::createOfferStream()
{
  QTextStream	stream(Socket::getInstance()->socket());
  Service*	service = Service::getInstance(this);

  stream << CREATE_OFFER_STREAM
	 << ' ' << service->offerStreamName->text()
	 << ' ' << service->offerStreamList->currentRow()
	 << ' ' << service->offerStreamTitle->text()
	 << endl;
}

void	Client::createWeb()
{
  QTextStream	stream(Socket::getInstance()->socket());
  Service*	service = Service::getInstance(this);

  stream << CREATE_WEB
	 << ' ' << service->webName->text()
	 << ' ' << service->webSpace->currentText()
	 << ' ' << service->webNbDb->currentText()
	 << ' ' << service->webDomain->text()
	 << endl;
}

void	Client::createStream()
{
  QTextStream	stream(Socket::getInstance()->socket());
  Service*	service = Service::getInstance(this);

  stream << CREATE_STREAM
	 << ' ' << service->streamName->text()
	 << ' ' << service->streamSlots->currentText()
	 << ' ' << service->streamBits->currentText()
	 << ' ' << service->streamTitle->text()
	 << endl;
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

const int&	Client::getCredit() const
{
  return (this->_credit);
}

void	Client::setCredit(const int& credit)
{
  this->_credit = credit;
  this->creditCurrently->setText(QVariant(this->_credit).toString());
}

void	Client::addCredit(const int& value)
{
  this->_credit += value;
  this->creditCurrently->setText(QVariant(this->_credit).toString());
}

void	Client::subCredit(const int& value)
{
  this->_credit -= value;
  this->creditCurrently->setText(QVariant(this->_credit).toString());
}
