//
// Client.cpp for Client in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Jul 15 15:29:04 2008 caner candan
// Last update Mon Aug 18 10:11:35 2008 caner candan
//

#include <QtNetwork>
#include <QMessageBox>
#include <QTextStream>
#include <QTime>
#include "Client.h"
#include "Connect.h"
#include "Create.h"
#include "State.h"

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
  : QMainWindow(parent), _socket(new QTcpSocket),
    _id(0), _credit(0)
{
  setupUi(this);
  actionSignUp->setEnabled(false);
  actionSignIn->setEnabled(false);
  actionSignOut->setEnabled(false);
  actionRefresh->setEnabled(false);
  pageBox->setEnabled(false);
  connect(_socket, SIGNAL(connected()),
	  this, SLOT(connectedToServer()));
  connect(_socket, SIGNAL(readyRead()),
	  this, SLOT(readAction()));
  connect(_socket, SIGNAL(bytesWritten(qint64)),
	  this, SLOT(sendAction()));
  connect(_socket, SIGNAL(error(QAbstractSocket::SocketError)),
	  this, SLOT(displayError(QAbstractSocket::SocketError)));
  connect(this->pageBox, SIGNAL(currentChanged(int)),
	  this, SLOT(loadPages(int)));
  connect(this->serviceBox, SIGNAL(currentChanged(int)),
	  this, SLOT(loadServices(int)));
  connect(this->creditBox, SIGNAL(currentChanged(int)),
	  this, SLOT(loadHistory(int)));
  _socket->connectToHost(HOST, PORT);
  if (!connectToDatabase())
    setEnabled(false);
}

Client::~Client()
{
  closeSocket();
  delete _socket;
  Service::kill();
  Web::kill();
  Stream::kill();
  Credit::kill();
  destroyMessages();
}

bool	Client::connectToDatabase()
{
  this->_db = QSqlDatabase::addDatabase("QSQLITE");
  this->_db.setDatabaseName(DBFILE);
  if (!this->_db.open())
    {
      QMessageBox::critical(this,
			    tr("Unable to connect to database"),
			    tr("An error occured: ")
			    + this->_db.lastError().text());
      return (false);
    }
  return (true);
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

void	Client::sendMessage(Message* mesg)
{
  QTextStream		stream(this->_socket);
  const QString&	from = mesg->from->text();
  const QString&	to = mesg->to->text();
  const QString&	edit = mesg->edit->text();

  if (edit.isEmpty())
    return;
  stream << MESSAGE << ' ' << to << ' ' << edit << endl;
  this->appendMessage(to, from, edit);
  mesg->edit->clear();
  mesg->edit->setFocus();
}

void	Client::appendMessage(const QString& sName,
			      const QString& from,
			      const QString& body)
{
  const QString&	time = QTime::currentTime().toString();
  QTextEdit		*list = this->_mm[sName]->list;

  list->append('[' + time + "] " + from + "> " + body);
}

void	Client::closeSocket()
{
  if (this->_socket->state()
      == QAbstractSocket::ConnectedState)
    this->_socket->close();
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
  this->talkList->clear();
  if (Service::exist())
    {
      Service*	service = Service::getInstance(this);

      service->offerWebList->clear();
      service->offerStreamList->clear();
    }
}

void	Client::on_actionSignUp_triggered()
{
  Create	create(this);
  QTextStream	stream(this->_socket);

  if (create.exec() != QDialog::Accepted)
    return;
  stream << CREATE
	 << ' ' << create.username->text()
	 << endl;
}

void	Client::on_actionSignIn_triggered()
{
  Connect	connect(this);
  QTextStream	stream(this->_socket);

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
  QTextStream	stream(this->_socket);

  stream << LOGOUT << endl;
}

void	Client::on_actionRefresh_triggered()
{
  QTextStream	stream(this->_socket);
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
  QTextStream	stream(this->_socket);
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
  QTextStream	stream(this->_socket);

  if (this->newsList->currentRow() >= 0)
    stream << NEWS_DETAIL
	   << ' ' << this->newsList->currentRow()
	   << endl;
}

void	Client::on_talkOpen_clicked()
{
  QString	sName;
  int		row;

  if ((row = this->talkList->currentRow()) < 0)
    return;
  sName = this->talkList->item(row)->text();
  this->openMessage(sName);
}

void	Client::connectedToServer()
{
  this->statusbar->showMessage("Connected to server");
  actionSignUp->setEnabled(true);
  actionSignIn->setEnabled(true);
}

void	Client::readAction()
{
  static fct	func = NULL;
  QString	res;
  QStringList	resList;
  int		i;

  while (this->_socket->canReadLine())
    {
      res = this->_socket->readLine();
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
  QMessageBox::critical(this,
			tr("Not connected"),
			tr("This address isn't a server"));
  this->logout();
  this->close();
}

void	Client::loadOffers(int idx)
{
  QTextStream	stream(this->_socket);
  Service	*service = Service::getInstance(this);

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
  QTextStream	stream(this->_socket);

  if (idx == 1) // services
    this->loadServices(0);
  else if (idx == 2) // credit
    this->loadHistory(0);
  else if (idx == 3) // talk
    this->loadClients();
}

void	Client::loadServices(int idx)
{
  QTextStream	stream(this->_socket);
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
  QTextStream	stream(this->_socket);

  this->talkList->clear();
  stream << CLIENTS << endl;
}

void	Client::loadHistory(int idx)
{
  QSqlQuery	q(this->_db);
  QListWidget*	list;
  ServiceType	type;

  q.prepare("select describe, date "
	    "from history "
	    "where id_user = ? and type = ? "
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
  q.addBindValue(this->getId());
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
  QTextStream	stream(this->_socket);
  Service*	service = Service::getInstance(this);

  stream << CREATE_OFFER_WEB
	 << ' ' << service->offerWebName->text()
	 << ' ' << service->offerWebList->currentRow()
	 << ' ' << service->offerWebDomain->text()
	 << endl;
}

void	Client::createOfferStream()
{
  QTextStream	stream(this->_socket);
  Service*	service = Service::getInstance(this);

  stream << CREATE_OFFER_STREAM
	 << ' ' << service->offerStreamName->text()
	 << ' ' << service->offerStreamList->currentRow()
	 << ' ' << service->offerStreamTitle->text()
	 << endl;
}

void	Client::createWeb()
{
  QTextStream	stream(this->_socket);
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
  QTextStream	stream(this->_socket);
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
  client->setCredit(resList.at(0).toInt());
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
  QMessageBox::information(client,
			   tr("Created"),
			   tr("Your account has been created and "
			      "your password is ") + resList.at(0));
  client->statusbar->showMessage("Accout created ...");
}

void	Client::actStatus(Client*, const QStringList&)
{}

void	Client::actClients(Client* client, const QStringList& resList)
{
  if (resList.count() < 1)
    return;

  const QString&	name = resList.at(0);
  QListWidgetItem*	item;

  if (name == client->infoAccount->text())
    return;
  qDebug() << "add client" << name;
  item = new QListWidgetItem(QIcon("images/user.png"), name);
  client->talkList->addItem(item);
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

const int&	Client::getId() const
{
  return (this->_id);
}

void	Client::setId(const int& id)
{
  this->_id = id;
}

const int&	Client::getCredit() const
{
  return (this->_credit);
}

void	Client::setCredit(const int& credit)
{
  this->_credit = credit;
}

void	Client::addHistory(const Client::ServiceType& type,
			   const QString& describe,
			   const int& price)
{
  QSqlQuery	q(this->_db);

  q.prepare("insert into history values(null, ?, ?, ?, ?, ?);");
  q.addBindValue(this->getId());
  q.addBindValue(type);
  q.addBindValue(describe);
  q.addBindValue(price);
  q.addBindValue(-1);
  q.exec();
}
