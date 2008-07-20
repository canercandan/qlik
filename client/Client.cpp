//
// Client.cpp for Client in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Jul 15 15:29:04 2008 caner candan
// Last update Sun Jul 20 19:30:51 2008 caner candan
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
  actionSignOut->setEnabled(false);
  connect(_socket, SIGNAL(readyRead()),
	  this, SLOT(readAction()));
  connect(_socket, SIGNAL(bytesWritten(qint64)),
	  this, SLOT(sendAction()));
  connect(_socket, SIGNAL(error(QAbstractSocket::SocketError)),
	  this, SLOT(displayError(QAbstractSocket::SocketError)));
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

  if (create.exec() != QDialog::Accepted)
    return;
}

void	Client::on_actionSignIn_triggered()
{
  Connect	connect(this);

  if (connect.exec() != QDialog::Accepted)
    return;
  this->closeSocket();
  this->_socket->connectToHost(connect.address->text(),
			       connect.port->text().toInt());
  this->_username = connect.username->text();
  this->_password = connect.password->text();
  this->connect(this->_socket, SIGNAL(connected()),
		this, SLOT(signIn()));
}

void	Client::on_actionSignOut_triggered()
{
  this->signOut();
  this->actionSignUp->setEnabled(true);
  this->actionSignIn->setEnabled(true);
  this->actionSignOut->setEnabled(false);
}

void	Client::on_actionQuit_triggered()
{
  this->close();
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
	qDebug() << "welcome";
      if (action >= 0 && action < NB_ACTIONS)
	{
	  qDebug() << "action found" << action;
	  actions[action].func(this, resList);
	}
    }
}

void	Client::sendAction()
{}

void	Client::signIn()
{
  QTextStream	stream(this->_socket);

  stream << LOGIN
	 << ' ' << this->_username
	 << ' ' << this->_password
	 << endl;
  this->_socket->waitForBytesWritten(1000);
}

void	Client::signUp()
{
  QTextStream	stream(this->_socket);

  stream << CREATE
	 << ' ' << this->_username
	 << ' ' << this->_password
	 << endl;
}

void	Client::signOut()
{
  QTextStream	stream(this->_socket);

  stream << LOGOUT << endl;
}

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
      return;
    }
  QMessageBox::information(client,
			   tr("Connected"),
			   tr("You're connected in your account."));
  client->actionSignUp->setEnabled(false);
  client->actionSignIn->setEnabled(false);
  client->actionSignOut->setEnabled(true);
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
  QMessageBox::information(client,
			   tr("Logout"),
			   tr("You're logout now"));
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
