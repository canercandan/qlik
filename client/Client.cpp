//
// Client.cpp for Client in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Jul 15 15:29:04 2008 caner candan
// Last update Tue Jul 15 18:56:14 2008 caner candan
//

#include "Client.h"
#include "Account.h"

Client::Client(QWidget *parent /*= NULL*/)
  : QMainWindow(parent)
{
  setupUi(this);
  actionSignOut->setEnabled(false);
}

Client::~Client()
{}

void	Client::on_actionSignIn_triggered()
{
  Account	account(this);

  if (account.exec() != QDialog::Accepted)
    return;
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
