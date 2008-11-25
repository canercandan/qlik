//
// AccountsAdmin.cpp for client in /home/candan_c/cu/rendu/qlik/client/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Mon Nov 24 00:57:18 2008 caner candan
// Last update Tue Nov 25 13:43:31 2008 caner candan
//

#include "AccountsAdmin.h"
#include "Client.h"
#include "Socket.h"
#include "Protocole.h"

AccountsAdmin::AccountsAdmin(QWidget* parent /*= NULL*/)
  : QDialog(parent)
{
  setupUi(this);
}

void	AccountsAdmin::on_minus_clicked()
{
  int	credit = this->newCredit->text().toInt();

  if (credit > 0)
    credit--;

  this->newCredit->setText(QVariant(credit).toString());
}

void	AccountsAdmin::on_plus_clicked()
{
  int	credit = this->newCredit->text().toInt();

  if (credit >= 0)
    credit++;

  this->newCredit->setText(QVariant(credit).toString());
}

void	AccountsAdmin::on_ok_clicked()
{
  int	right = 0;

  if (this->rightMessage->isChecked())
    right |= RIGHT_MESSAGE;
  if (this->rightWeb->isChecked())
    right |= RIGHT_WEB;
  if (this->rightStream->isChecked())
    right |= RIGHT_STREAM;
  if (this->rightNews->isChecked())
    right |= RIGHT_NEWS;
  if (this->rightServer->isChecked())
    right |= RIGHT_SERVER;
  if (this->rightAdmin->isChecked())
    right |= RIGHT_ADMIN;

  QTextStream	stream(Socket::getInstance()->socket());

  stream << ACCOUNTS_MODIFY
	 << SP << this->account->text()
	 << SP << this->newCredit->text()
	 << SP << right
	 << NL;
}

void	AccountsAdmin::on_cancel_clicked()
{
  this->hide();
}
