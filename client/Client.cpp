//
// Client.cpp for Client in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Jul 15 15:29:04 2008 caner candan
// Last update Tue Aug  5 20:57:57 2008 caner candan
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
  {OFFER_WEB, actOfferWeb},
  {OFFER_STREAM, actOfferStream},
  {SERVICES_WEB, actServicesWeb},
  {SERVICES_STREAM, actServicesStream},
  {CREATE_SERVICE, actCreateService},
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
  this->_mm[sName]->messageFrom->setText(this->infoAccount->text());
  this->_mm[sName]->messageTo->setText(sName);
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
  const QString&	to = mesg->messageTo->text();
  const QString&	from = mesg->messageTo->text();
  const QString&	edit = mesg->messageEdit->text();

  qDebug() << to << from << edit;
  if (edit.isEmpty() || to.isEmpty() || from.isEmpty())
    return;
  stream << MESSAGE << ' ' << to << ' ' << edit << endl;
  this->appendMessage(from, edit);
  mesg->messageEdit->clear();
  mesg->messageEdit->setFocus();
}

void	Client::appendMessage(const QString& sName,
			      const QString& body)
{
  QListWidgetItem	*item;
  QString		date;

  QTime::fromString(date);
  qDebug() << date;
  item = new QListWidgetItem(sName + "> " + body);
  this->_mm[sName]->listMessage->addItem(item);
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
  this->pageBox->setEnabled(true);
  this->infoStatus->setText("Online");
  this->statusbar->showMessage("I'm sign in ...");
  this->on_refreshNews_clicked();
}

void	Client::logout()
{
  this->actionSignUp->setEnabled(true);
  this->actionSignIn->setEnabled(true);
  this->actionSignOut->setEnabled(false);
  this->pageBox->setEnabled(false);
  this->infoAccount->setText("guest");
  this->infoStatus->setText("Offline");
  this->statusbar->showMessage("I'm sign out ...");
  this->pageBox->setCurrentIndex(0);
  this->destroyMessages();
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

void	Client::on_addService_clicked()
{
  this->_service = new Service(this);
  connect(this->_service->serviceBox, SIGNAL(currentChanged(int)),
	  this, SLOT(loadOffers(int)));
  this->loadOffers(0);
  if (this->_service->exec() != QDialog::Accepted)
    {
      delete this->_service;
      return;
    }
  delete this->_service;
}

void	Client::on_refreshNews_clicked()
{
  QTextStream	stream(this->_socket);

  this->newsList->clear();
  stream << NEWS << endl;
}

void	Client::on_readNews_clicked()
{
  QTextStream	stream(this->_socket);

  if (this->newsList->currentRow() >= 0)
    stream << NEWS_DETAIL
	   << ' ' << this->newsList->currentRow()
	   << endl;
}

void		Client::on_talkOpen_clicked()
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
      this->_service->offerWebList->clear();
      stream << OFFER_WEB << endl;
      return;
    }
  this->_service->offerStreamList->clear();
  stream << OFFER_STREAM << endl;
}

void	Client::loadPages(int idx)
{
  QTextStream	stream(this->_socket);

  if (idx == 1)
    loadServices(0);
}

void	Client::loadServices(int idx)
{
  QTextStream	stream(this->_socket);

  if (!idx)
    {
      this->serviceWebList->clear();
      stream << SERVICES_WEB << endl;
      return;
    }
  this->serviceStreamList->clear();
  this->serviceStreamList->clear();
  stream << SERVICES_STREAM << endl;
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

void	Client::actClients(Client*, const QStringList&)
{}

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
  client->appendMessage(to, resMessage.join(" "));
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

void	Client::actCreateService(Client*, const QStringList&)
{}

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
