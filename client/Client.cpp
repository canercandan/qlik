//
// Client.cpp for Client in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Jul 15 15:29:04 2008 caner candan
// Last update Wed Aug 20 09:08:56 2008 caner candan
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

Client::Actions	Client::actions[] =
  {
    {WELCOME, actWelcome},
    {LOGIN, actLogin},
    {LOGOUT, actLogout},
    {CREATE, actCreate},
    {STATUS, actStatus},
    {CLIENTS, actClients},
    {ACCOUNTS, actAccounts},
    {MESSAGE, actMessage},
    {SERVICES_WEB, actServicesWeb},
    {SERVICES_STREAM, actServicesStream},
    {SERVICES_WEB_DETAIL, actServicesWebDetail},
    {SERVICES_STREAM_DETAIL, actServicesStreamDetail},
    {OFFER_WEB, actOfferWeb},
    {OFFER_STREAM, actOfferStream},
    {CREATE_OFFER_WEB, actCreateOfferWeb},
    {CREATE_OFFER_STREAM, actCreateOfferStream},
    {CREATE_WEB, actCreateWeb},
    {CREATE_STREAM, actCreateStream},
    {NEWS, actNews},
    {NEWS_DETAIL, actNewsDetail},
    {NULL, NULL}
  };

Client::Client(QWidget *parent /*= NULL*/)
  : QMainWindow(parent)
{
  Socket*	socket = Socket::getInstance();
  Database*	database = Database::getInstance();

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
  if (!database->connect())
    {
      QMessageBox::critical(this,
			    tr("Unable to connect to database"),
			    tr("An error occured: ")
			    + database->database().lastError().text());
      setEnabled(false);
    }
  Options::getInstance(this);
}

Client::~Client()
{
  Socket::kill();
  Database::kill();
  Service::kill();
  Web::kill();
  Stream::kill();
  Credit::kill();
  destroyMessages();
}

void	Client::openMessage(const QString& sName)
{
  if (!this->_mm.contains(sName) ||
      !this->_mm[sName])
    this->_mm[sName] = new Message(this);
  this->_mm[sName]->from->setText(this->infoAccount->text());
  this->_mm[sName]->to->setText(sName);
  this->_mm[sName]->show();
}

void	Client::destroyMessages()
{
  MessageMap::iterator	it;
  MessageMap::iterator	end = this->_mm.end();

  for (it = this->_mm.begin(); it != end; ++it)
    {
      if (it.value())
	{
	  it.value()->close();
	  delete it.value();
	}
      this->_mm[it.key()] = NULL;
    }
}

void	Client::appendMessage(const QString& sName,
			      const QString& from,
			      const QString& body)
{
  const QString&	time = QTime::currentTime().toString();
  QTextEdit		*list = this->_mm[sName]->list;

  list->append('[' + time + "] " + from + "> " + body);
}

void	Client::login()
{
  this->actionSignUp->setEnabled(false);
  this->actionSignIn->setEnabled(false);
  this->actionSignOut->setEnabled(true);
  this->actionRefresh->setEnabled(true);
  this->pageBox->setEnabled(true);
  this->infoStatus->setText("Online");
  this->statusbar->showMessage("I'm sign in ...");
  this->on_actionRefresh_triggered();
}

void	Client::logout()
{
  this->actionSignUp->setEnabled(true);
  this->actionSignIn->setEnabled(true);
  this->actionSignOut->setEnabled(false);
  this->actionRefresh->setEnabled(false);
  this->pageBox->setEnabled(false);
  this->infoAccount->setText("guest");
  this->infoStatus->setText("Offline");
  this->statusbar->showMessage("I'm sign out ...");
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
  this->_userCreated = create.username->text();
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

void	Client::on_actionInformation_triggered()
{
  QMessageBox::information(this,
			   tr("Information"),
			   tr("Information about this program"));
}

void	Client::on_actionHelp_triggered()
{
  QMessageBox::information(this,
			   tr("Help"),
			   tr("Help about this soft"));
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
  int		row;

  if (!this->serviceBox->currentIndex())
    {
      if ((row = this->serviceWebList->currentRow()) < 0)
	return;
      stream << SERVICES_WEB_DETAIL
	     << ' ' << row
	     << endl;
      Web::getInstance(this)->show();
    }
  else
    {
      if ((row = this->serviceStreamList->currentRow()) < 0)
	return;
      stream << SERVICES_STREAM_DETAIL
	     << ' ' << row
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
	   << ' ' << this->newsList->currentRow()
	   << endl;
}

void	Client::on_talkOpen_clicked()
{
  QString	sName;

  if (!this->talkBox->currentIndex())
    {
      if (this->talkMyContactsList->currentRow() < 0)
	return;
      this->openMessage(this->talkMyContactsList->currentItem()->data(Qt::UserRole).toString());
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

  if (QMessageBox::question(this,
			    tr("Are you sure ?"),
			    tr("Are you sure ?"),
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
  this->statusbar->showMessage("Connected to server");
  this->setEnabled(true);
  this->actionSignUp->setEnabled(true);
  this->actionSignIn->setEnabled(true);
}

void	Client::readAction()
{
  static fct	func = NULL;
  QString	res;
  QStringList	resList;
  int		i;
  Socket*	socket = Socket::getInstance();

  while (socket->socket()->canReadLine())
    {
      res = socket->socket()->readLine();
      qDebug() << "res" << res;
      resList = res.split(QRegExp("\\s+"));
      if (func)
	{
	  if (resList.at(0) == "END")
	    {
	      qDebug() << "i stop";
	      func = NULL;
	    }
	  else
	    func(this, resList);
	}
      else
	{
	  for (i = 0; actions[i].func; i++)
	    if (actions[i].keyword == resList.at(0))
	      {
		qDebug() << "action found" << resList.at(0);
		resList.erase(resList.begin());
		if (resList.at(0) == "BEGIN")
		  {
		    qDebug() << "i start";
		    resList.erase(resList.begin());
		    func = actions[i].func;
		  }
		else
		  actions[i].func(this, resList);
		break;
	      }
	}
    }
}

void	Client::sendAction()
{}

void	Client::displayError(QAbstractSocket::SocketError)
{
  Options*	options = Options::getInstance(this);

  QMessageBox::critical(this,
			tr("Not connected"),
			tr("This address isn't a server"));
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
      stream << SERVICES_WEB << endl;
      state->setWebList(State::DONE);
      return;
    }
  if (state->getStreamList() == State::DONE)
    return;
  this->serviceStreamList->clear();
  stream << SERVICES_STREAM << endl;
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
      type = WEB;
      list = this->creditWebList;
    }
  else // stream
    {
      type = STREAM;
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

void	Client::actWelcome(Client* client, const QStringList&)
{
  client->statusbar->showMessage("Welcome");
}

void	Client::actLogin(Client* client, const QStringList& resList)
{
  if (resList.at(0) == "KO")
    {
      QMessageBox::critical(client,
			    tr("Login incorrect"),
			    tr("Username or password incorrect"));
      client->logout();
      return;
    }
  client->creditCurrently->setText(resList.at(0));
  client->login();
}

void	Client::actLogout(Client* client, const QStringList& resList)
{
  if (resList.at(0) != "OK")
    {
      QMessageBox::critical(client,
			    tr("Logout error"),
			    tr("Logout error"));
      return;
    }
  client->logout();
}

void	Client::actCreate(Client* client, const QStringList& resList)
{
  if (resList.at(0) == "KO")
    {
      QMessageBox::critical(client,
			    tr("Creation incorrect"),
			    tr("Username already used or incorrect"));
      return;
    }
  if (QMessageBox::question(client,
			    tr("Created"),
			    tr("Your account has been created and "
			       "your password is ") + resList.at(0)
			    + tr("\n\nWould you like to save your "
				 "account in the account's list ?"),
			    QMessageBox::Yes | QMessageBox::No)
      == QMessageBox::Yes)
    {
      QSqlQuery	q(Database::getInstance()->database());

      q.prepare("insert into users "
		"values(?, ?);");
      q.addBindValue(client->_userCreated);
      q.addBindValue(resList.at(0));
      q.exec();
      Accounts::getInstance(client)->reset();
    }
  client->statusbar->showMessage("Accout created ...");
}

void	Client::actStatus(Client*, const QStringList&)
{}

void	Client::actClients(Client* client, const QStringList& resList)
{
  if (resList.count() < 1)
    return;

  const QString&	name = resList.at(0);

  if (name == client->infoAccount->text())
    return;
  qDebug() << "add client" << name;
  client->loadAllContact(name);
  client->loadMyContact(name);
}

void	Client::actAccounts(Client*, const QStringList&)
{}

void	Client::actMessage(Client* client, const QStringList& resList)
{
  const QString&	to = resList.at(0);

  if (to == "KO")
    {
      QMessageBox::critical(client,
			    tr("Message error"),
			    tr("Message error"));
      return;
    }
  if (to == "OK")
    return;
  client->openMessage(to);

  QStringList	resMessage = resList;

  resMessage.erase(resMessage.begin());
  client->appendMessage(to, to, resMessage.join(" "));
}

void	Client::actServicesWeb(Client* client, const QStringList& resList)
{
  if (resList.count() < 1)
    return;

  const QString&	name = resList.join(" ");

  qDebug() << "add service web" << name;
  client->serviceWebList->addItem(new QListWidgetItem
				  (QIcon("images/bricks.png"), name));
}

void	Client::actServicesStream(Client* client, const QStringList& resList)
{
  if (resList.count() < 1)
    return;

  const QString&	name = resList.join(" ");

  qDebug() << "add service stream" << name;
  client->serviceStreamList->addItem(new QListWidgetItem
				     (QIcon("images/bricks.png"), name));
}

void	Client::actServicesWebDetail(Client* client, const QStringList& resList)
{
  if (resList.at(0) == "KO")
    {
      QMessageBox::critical(client,
			    tr("incorrect web service"),
			    tr("incorrect web service"));
      return;
    }

  Web*	web = Web::getInstance(client);

  web->name->setText(resList.at(0));
  web->space->setText(resList.at(1));
  web->nbDb->setText(resList.at(2));
  web->domain->setText(resList.at(3));
}

void	Client::actServicesStreamDetail(Client* client, const QStringList& resList)
{
  if (resList.at(0) == "KO")
    {
      QMessageBox::critical(client,
			    tr("incorrect stream service"),
			    tr("incorrect stream service"));
      return;
    }

  Stream*	stream = Stream::getInstance(client);

  stream->name->setText(resList.at(0));
  stream->slotss->setText(resList.at(1));
  stream->bits->setText(resList.at(2));
  stream->title->setText(resList.at(3));
}

void	Client::actOfferWeb(Client* client, const QStringList& resList)
{
  if (resList.count() < 1)
    return;

  const QString&	name = resList.join(" ");

  qDebug() << "add offer web" << name;
  Service::getInstance(client)->offerWebList->addItem(new QListWidgetItem
						      (QIcon("images/bricks.png"), name));
}

void	Client::actOfferStream(Client* client, const QStringList& resList)
{
  if (resList.count() < 1)
    return;

  const QString&	name = resList.join(" ");

  qDebug() << "add offer stream" << name;
  Service::getInstance(client)->offerStreamList->addItem(new QListWidgetItem
							 (QIcon("images/bricks.png"), name));
}

void	Client::actCreateOfferWeb(Client* client, const QStringList& resList)
{
  if (resList.at(0) == "KO")
    {
      QMessageBox::critical(client,
			    tr("Error"),
			    tr("Impossible to create a web offer"));
      return;
    }
  QMessageBox::information(client,
			   tr("Created"),
			   tr("Your web offer has been created"));
  client->addHistory(WEB, "create offer", -1);
  State::getInstance()->setWebList(State::WAIT);
  client->on_actionRefresh_triggered();
  Service::getInstance(client)->hide();
}

void	Client::actCreateOfferStream(Client* client, const QStringList& resList)
{
  if (resList.at(0) == "KO")
    {
      QMessageBox::critical(client,
			    tr("Error"),
			    tr("Impossible to create a stream offer"));
      return;
    }
  QMessageBox::information(client,
			   tr("Created"),
			   tr("Your stream offer has been created"));
  client->addHistory(STREAM, "create offer", -1);
  State::getInstance()->setStreamList(State::WAIT);
  client->on_actionRefresh_triggered();
  Service::getInstance(client)->hide();
}

void	Client::actCreateWeb(Client* client, const QStringList& resList)
{
  if (resList.at(0) == "KO")
    {
      QMessageBox::critical(client,
			    tr("Error"),
			    tr("Impossible to create a web"));
      return;
    }
  QMessageBox::information(client,
			   tr("Created"),
			   tr("Your web has been created"));
  client->addHistory(WEB, "create", -1);
  State::getInstance()->setWebList(State::WAIT);
  client->on_actionRefresh_triggered();
  Service::getInstance(client)->hide();
}

void	Client::actCreateStream(Client* client, const QStringList& resList)
{
  if (resList.at(0) == "KO")
    {
      QMessageBox::critical(client,
			    tr("Error"),
			    tr("Impossible to create a stream"));
      return;
    }
  QMessageBox::information(client,
			   tr("Created"),
			   tr("Your stream has been created"));
  client->addHistory(STREAM, "create", -1);
  State::getInstance()->setStreamList(State::WAIT);
  client->on_actionRefresh_triggered();
  Service::getInstance(client)->hide();
}

void	Client::actNews(Client* client, const QStringList& resList)
{
  if (resList.count() < 2)
    return;

  int		date = resList.at(0).toInt();
  QString	sDate(::ctime((time_t*)&date));
  QStringList	resMessage = resList;

  resMessage.erase(resMessage.begin());

  const QString&	subject = resMessage.join(" ");

  qDebug() << "add news" << subject << date;
  qDebug() << sDate;
  client->newsList->addItem(sDate + ' ' + subject);
  client->actionRefresh->setEnabled(true);
}

void	Client::actNewsDetail(Client* client, const QStringList& resList)
{
  if (resList.at(0) != "KO")
    QMessageBox::information(client,
			     tr("Message"),
			     resList.join(" "));
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
