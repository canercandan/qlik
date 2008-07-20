//
// Socket.cpp for Socket in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Wed Jul 16 23:22:27 2008 caner candan
// Last update Sun Jul 20 13:22:45 2008 caner candan
//

#include <QMessageBox>
#include "Socket.h"
#include "Client.h"

Socket::Actions	Socket::actions[NB_ACTIONS] = {
  {actLogin}, {actLogout}, {actCreate}, {actStatus},
  {actClients}, {actAccounts}, {actMessage},
  {actServices}, {actCreateService}
};

Socket::Socket(QWidget *parent /*= NULL*/)
  : _parent(parent), _socket(new QTcpSocket)
{}

Socket::~Socket()
{
  close();
  delete _socket;
}

void	Socket::connectToServer(const Connect& connect)
{
  if (this->_socket->state() == QAbstractSocket::ConnectedState)
    this->close();
  this->_socket->connectToHost(connect.address->text(),
			       connect.port->text().toInt());
  this->_username = connect.username->text();
  this->_password = connect.password->text();
  this->connect(this->_socket, SIGNAL(connected()),
		this, SLOT(signIn()));
  this->connect(this->_socket, SIGNAL(readyRead()),
		this, SLOT(executeAction()));
  this->connect(this->_socket, SIGNAL(error(QAbstractSocket::SocketError)),
		this, SLOT(displayError(QAbstractSocket::SocketError)));
}

void	Socket::createToServer(const Create& create)
{
  if (this->_socket->state() == QAbstractSocket::ConnectedState)
    this->close();
  this->_socket->connectToHost(create.address->text(),
			       create.port->text().toInt());
  this->_username = create.username->text();
  this->_password = create.password->text();
  this->connect(this->_socket, SIGNAL(connected()),
		this, SLOT(signUp()));
  this->connect(this->_socket, SIGNAL(readyRead()),
		this, SLOT(executeAction()));
  this->connect(this->_socket, SIGNAL(error(QAbstractSocket::SocketError)),
		this, SLOT(displayError(QAbstractSocket::SocketError)));
}

void	Socket::close(void)
{
  this->_socket->close();
}

void	Socket::signIn()
{
  QTextStream	stream(this->_socket);

  stream << LOGIN
	 << ' ' << this->_username
	 << ' ' << this->_password
	 << '\n';
}

void	Socket::signUp()
{
  QTextStream	stream(this->_socket);

  qDebug() << CREATE
	   << ' ' << this->_username
	   << ' ' << this->_password
	   << '\n';
  stream << CREATE
	 << ' ' << this->_username
	 << ' ' << this->_password
	 << '\n';
}

QTcpSocket	*Socket::getSocket(void)
{
  return (this->_socket);
}

void	Socket::executeAction()
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

void	Socket::displayError(QAbstractSocket::SocketError)
{
  QMessageBox::critical(this->_parent,
			tr("Not connected"),
			tr("This address isn't a server"));
}

void	Socket::actLogin(Socket* socket, const QStringList& resList)
{
  qDebug() << "actLogin" << resList.at(1);
  if (resList.at(1) != "OK")
    {
      QMessageBox::critical(socket->_parent,
			    tr("Login incorrect"),
			    tr("Username or password incorrect"));
      return;
    }
  else
    QMessageBox::information(socket->_parent,
			     tr("Connected"),
			     tr("You're connected in your account."));
  ((Client*)socket->_parent)->actionSignUp->setEnabled(false);
  ((Client*)socket->_parent)->actionSignIn->setEnabled(false);
  ((Client*)socket->_parent)->actionSignOut->setEnabled(true);
}

void	Socket::actLogout(Socket*, const QStringList&)
{}

void	Socket::actCreate(Socket*, const QStringList&)
{}

void	Socket::actStatus(Socket*, const QStringList&)
{}

void	Socket::actClients(Socket*, const QStringList&)
{}

void	Socket::actAccounts(Socket*, const QStringList&)
{}

void	Socket::actMessage(Socket*, const QStringList&)
{}

void	Socket::actServices(Socket*, const QStringList&)
{}

void	Socket::actCreateService(Socket*, const QStringList&)
{}
