//
// Client.cpp for Client in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Jul 15 15:29:04 2008 caner candan
// Last update Fri Aug  8 13:08:36 2008 caner candan
//

#include <QtNetwork>
#include <QMessageBox>
#include <QTextStream>
#include <QTime>
#include "Client.h"
#include "Connect.h"
#include "Create.h"

Client::Actions	Client::actions[] = {
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
  : QMainWindow(parent), _socket(new QTcpSocket), _service(NULL)
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
  _socket->connectToHost(HOST, PORT);
}

Client::~Client()
{
  closeSocket();
  delete _socket;
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
  if (this->_service)
    {
      this->_service->offerWebList->clear();
      this->_service->offerStreamList->clear();
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
	 << ' ' << create.password->text()
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
  if (!idx)
    {
      this->newsList->clear();
      stream << NEWS << endl;
    }
  else if (idx == 1)
    {
      if (!this->serviceBox->currentIndex())
	{
	  this->serviceWebList->clear();
	  this->loadServices(0);
	}
      else
	{
	  this->serviceStreamList->clear();
	  this->loadServices(1);
	}
    }
  else if (idx == 3)
    {
      this->talkList->clear();
      this->loadClients();
    }
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
  if (!this->_service)
    this->_service = new Service(this);
  connect(this->_service->serviceBox, SIGNAL(currentChanged(int)),
	  this, SLOT(loadOffers(int)));
  if (!this->serviceBox->currentIndex())
    {
      this->loadOffers(0);
      this->_service->serviceBox->setCurrentIndex(0);
    }
  else
    {
      this->loadOffers(1);
      this->_service->serviceBox->setCurrentIndex(1);
    }
  this->_service->show();
}

void	Client::on_serviceManage_clicked()
{}

void	Client::on_serviceCredit_clicked()
{}

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
}

void	Client::loadOffers(int idx)
{
  QTextStream	stream(this->_socket);

  if (!idx)
    {      
      if (this->_service->offerWebList->count())
	return;
      stream << OFFER_WEB << endl;
      return;
    }
  if (this->_service->offerStreamList->count())
    return;
  stream << OFFER_STREAM << endl;
}

void	Client::loadPages(int idx)
{
  QTextStream	stream(this->_socket);

  if (idx == 1)
    loadServices(0);
  else if (idx == 3)
    loadClients();
}

void	Client::loadServices(int idx)
{
  QTextStream	stream(this->_socket);

  if (!idx)
    {
      if (this->serviceWebList->count())
	return;
      stream << SERVICES_WEB << endl;
      return;
    }
  if (this->serviceStreamList->count())
    return;
  stream << SERVICES_STREAM << endl;
}

void	Client::loadClients()
{
  QTextStream	stream(this->_socket);

  stream << CLIENTS << endl;
}

void	Client::createOfferWeb()
{
  QTextStream	stream(this->_socket);

  stream << CREATE_OFFER_WEB
	 << ' ' << this->_service->offerWebName->text()
	 << ' ' << this->_service->offerWebList->currentRow()
	 << ' ' << this->_service->offerWebDomain->text()
	 << endl;
}

void	Client::createOfferStream()
{
  QTextStream	stream(this->_socket);

  stream << CREATE_OFFER_STREAM
	 << ' ' << this->_service->offerStreamName->text()
	 << ' ' << this->_service->offerStreamList->currentRow()
	 << ' ' << this->_service->offerStreamTitle->text()
	 << endl;
}

void	Client::createWeb()
{
  QTextStream	stream(this->_socket);

  stream << CREATE_WEB
	 << ' ' << this->_service->webName->text()
	 << ' ' << this->_service->webSpace->currentText()
	 << ' ' << this->_service->webNbDb->currentText()
	 << ' ' << this->_service->webDomain->text()
	 << endl;
}

void	Client::createStream()
{
  QTextStream	stream(this->_socket);

  stream << CREATE_STREAM
	 << ' ' << this->_service->streamName->text()
	 << ' ' << this->_service->streamSlots->currentText()
	 << ' ' << this->_service->streamBits->currentText()
	 << ' ' << this->_service->streamTitle->text()
	 << endl;
}

void	Client::actWelcome(Client* client, const QStringList&)
{
  client->statusbar->showMessage("Welcome");
}

void	Client::actLogin(Client* client, const QStringList& resList)
{
  if (resList.at(0) != "OK")
    {
      QMessageBox::critical(client,
			    tr("Login incorrect"),
			    tr("Username or password incorrect"));
      client->logout();
      return;
    }
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
  if (resList.at(0) != "OK")
    {
      QMessageBox::critical(client,
			    tr("Creation incorrect"),
			    tr("Username or password already used"));
      return;
    }
  QMessageBox::information(client,
			   tr("Created"),
			   tr("Your account has been created."));
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

void	Client::actOfferWeb(Client* client, const QStringList& resList)
{
  if (resList.count() < 1)
    return;

  const QString&	name = resList.join(" ");

  qDebug() << "add offer web" << name;
  client->_service->offerWebList->addItem(new QListWidgetItem
					  (QIcon("images/bricks.png"), name));
}

void	Client::actOfferStream(Client* client, const QStringList& resList)
{
  if (resList.count() < 1)
    return;

  const QString&	name = resList.join(" ");

  qDebug() << "add offer stream" << name;
  client->_service->offerStreamList->addItem(new QListWidgetItem
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
  client->on_actionRefresh_triggered();
  client->_service->hide();
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
  client->on_actionRefresh_triggered();
  client->_service->hide();
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
  client->on_actionRefresh_triggered();
  client->_service->hide();
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
  client->on_actionRefresh_triggered();
  client->_service->hide();
}

void	Client::actNews(Client* client, const QStringList& resList)
{
  if (resList.count() < 2)
    return;

  const QString&	subject = resList.at(0);
  int			date = resList.at(1).toInt();
  QString		sDate(ctime((time_t*)&date));

  qDebug() << "add news" << subject << date;
  qDebug() << sDate;
  client->newsList->addItem(sDate + ' ' + subject);
}

void	Client::actNewsDetail(Client* client, const QStringList& resList)
{
  if (resList.at(0) != "KO")
    QMessageBox::information(client,
			     tr("Message"),
			     resList.join(" "));
}
