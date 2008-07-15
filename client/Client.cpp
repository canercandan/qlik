//
// Client.cpp for Client in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Jul 15 15:29:04 2008 caner candan
// Last update Tue Jul 15 20:53:23 2008 caner candan
//

#include "Client.h"
#include "Connect.h"
#include "Create.h"

Client::Client(QWidget *parent /*= NULL*/)
  : QMainWindow(parent)
{
  setupUi(this);
  actionSignOut->setEnabled(false);
}

Client::~Client()
{}

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
  this->actionSignUp->setEnabled(false);
  this->actionSignIn->setEnabled(false);
  this->actionSignOut->setEnabled(true);
}

void	Client::on_actionSignOut_triggered()
{
  this->actionSignIn->setEnabled(true);
  this->actionSignOut->setEnabled(false);
}

void	Client::on_actionQuit_triggered()
{
  this->close();
}
