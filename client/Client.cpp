//
// Client.cpp for Client in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Jul 15 15:29:04 2008 caner candan
// Last update Sun Jul 20 22:56:05 2008 caner candan
//

#include "Client.h"
#include "Connect.h"
#include "Create.h"
#include <QtNetwork>
#include <QMessageBox>
#include <QTextStream>

Client::Actions	Client::actions[NB_ACTIONS] = {
  {actLogin}, {actLogout}, {actCreate}, {actStatus},
  {actClients}, {actAccounts}, {actMessage},
  {actServices}, {actCreateService}
};

Client::Client(QWidget *parent /*= NULL*/)
  : QMainWindow(parent), _socket(new QTcpSocket)
{
  setupUi(this);
  actionSignUp->setEnabled(false);
  actionSignIn->setEnabled(false);
  actionSignOut->setEnabled(false);
  toolBox->setEnabled(false);
  connect(_socket, SIGNAL(connected()),
	  this, SLOT(connectedToServer()));
  connect(_socket, SIGNAL(readyRead()),
	  this, SLOT(readAction()));
  connect(_socket, SIGNAL(bytesWritten(qint64)),
	  this, SLOT(sendAction()));
  connect(_socket, SIGNAL(error(QAbstractSocket::SocketError)),
	  this, SLOT(displayError(QAbstractSocket::SocketError)));
  _socket->connectToHost(HOST, PORT);
}

Client::~Client()
{
  closeSocket();
  delete _socket;
}

void	Client::closeSocket()
{
  if (this->_socket->state()
      == QAbstractSocket::ConnectedState)
    this->_socket->close();
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

void	Client::on_actionQuit_triggered()
{
  this->close();
}

void	Client::connectedToServer()
{
  this->statusbar->showMessage("Connected to server");
  actionSignUp->setEnabled(true);
  actionSignIn->setEnabled(true);
}

void	Client::readAction()
{
  QString	res;
  QStringList	resList;
  int		action;

  while (this->_socket->canReadLine())
    {
      res = this->_socket->readLine();
      resList = res.split(QRegExp("\\s+"));
      if (!resList.at(0).at(0).isNumber())
	return;
      action = resList.at(0).toInt();
      if (action == 42)
	this->statusbar->showMessage("Welcome");
      if (action >= 0 && action < NB_ACTIONS)
	{
	  qDebug() << "action found" << action;
	  actions[action].func(this, resList);
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
}

void	Client::actLogin(Client* client, const QStringList& resList)
{
  if (resList.at(1) != "OK")
    {
      QMessageBox::critical(client,
			    tr("Login incorrect"),
			    tr("Username or password incorrect"));
      client->infoAccount->setText("guest");
      client->infoStatus->setText("Offline");
      return;
    }
  client->actionSignUp->setEnabled(false);
  client->actionSignIn->setEnabled(false);
  client->actionSignOut->setEnabled(true);
  client->toolBox->setEnabled(true);
  client->infoStatus->setText("Online");
  client->statusbar->showMessage("I'm sign in ...");
}

void	Client::actLogout(Client* client, const QStringList& resList)
{
  if (resList.at(1) != "OK")
    {
      QMessageBox::critical(client,
			    tr("Logout error"),
			    tr("Logout error"));
      return;
    }
  client->actionSignUp->setEnabled(true);
  client->actionSignIn->setEnabled(true);
  client->actionSignOut->setEnabled(false);
  client->toolBox->setEnabled(false);
  client->infoAccount->setText("guest");
  client->infoStatus->setText("Offline");
  client->statusbar->showMessage("I'm sign out ...");
}

void	Client::actCreate(Client* client, const QStringList& resList)
{
  if (resList.at(1) != "OK")
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

void	Client::actMessage(Client*, const QStringList&)
{}

void	Client::actServices(Client*, const QStringList&)
{}

void	Client::actCreateService(Client*, const QStringList&)
{}
