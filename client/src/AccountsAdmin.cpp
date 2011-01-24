// AccountsAdmin.cpp --- 
// 
// Filename: AccountsAdmin.cpp
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Wed Nov 26 23:23:49 2008 (+0200)
// Version: 
// Last-Updated: Wed Nov 26 23:23:59 2008 (+0200)
//           By: Caner Candan
//     Update #: 1
// URL: 
// Keywords: 
// Compatibility: 
// 
// 

// Commentary: 
// 
// 
// 
// 

// Change log:
// 
// 
// 
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 3, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; see the file COPYING.  If not, write to
// the Free Software Foundation, Inc., 51 Franklin Street, Fifth
// Floor, Boston, MA 02110-1301, USA.
// 
// 

// Code:

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

// 
// AccountsAdmin.cpp ends here
