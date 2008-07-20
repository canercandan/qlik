//
// Client.cpp for Client in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Jul 15 15:29:04 2008 caner candan
// Last update Sun Jul 20 13:21:36 2008 caner candan
//

#include "Client.h"
#include "Connect.h"
#include "Create.h"
#include <QtNetwork>
#include <QMessageBox>
#include <QTextStream>

Client::Client(QWidget *parent /*= NULL*/)
  : QMainWindow(parent), _socket(new Socket(this))
{
  setupUi(this);
  actionSignOut->setEnabled(false);
}

Client::~Client()
{
  delete _socket;
}

void	Client::on_actionSignUp_triggered()
{
  Create	create(this);

  if (create.exec() != QDialog::Accepted)
    return;
  this->_socket->createToServer(create);
}

void	Client::on_actionSignIn_triggered()
{
  Connect	connect(this);

  if (connect.exec() != QDialog::Accepted)
    return;
  this->_socket->connectToServer(connect);
}

void	Client::on_actionSignOut_triggered()
{
  this->actionSignUp->setEnabled(true);
  this->actionSignIn->setEnabled(true);
  this->actionSignOut->setEnabled(false);
}

void	Client::on_actionQuit_triggered()
{
  this->close();
}
