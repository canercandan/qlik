// Connect.cpp --- 
// 
// Filename: Connect.cpp
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 00:51:13 2008 (+0200)
// Version: 
// Last-Updated: Thu Nov 27 00:51:18 2008 (+0200)
//           By: Caner Candan
//     Update #: 2
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

#include <QMessageBox>
#include "Connect.h"
#include "Database.h"
#include "Protocole.h"

Connect::Connect(QWidget* parent /*= NULL*/)
  : QDialog(parent)
{
  setupUi(this);
  _loadAccounts();
}

void	Connect::on_ok_clicked()
{
  if (!this->connectBox->currentIndex()) // accounts
    {
      QSqlQuery	q(Database::getInstance()->database());

      q.prepare("select username, password "
		"from users "
		"where username = ?;");
      q.addBindValue(this->accounts->currentText());
      q.exec();
      if (q.next())
	{
	  this->username->setText(q.value(0).toString());
	  this->password->setText(q.value(1).toString());
	}
    }
  if (this->username->text().isEmpty())
    {
      QMessageBox::information(this, tr("no_username"), tr("no_username_txt"));
      this->username->setFocus();
      return;
    }

  QRegExp	rx;

  rx.setPattern(PATTERN_USERNAME);

  if (rx.indexIn(this->username->text()) < 0)
    {
      QMessageBox::information(this, tr("username_inc"),
			       tr("username_inc_txt"));
      this->username->setFocus();
      return;
    }

  if (this->password->text().isEmpty())
    {
      QMessageBox::information(this, tr("no_password"),
			       tr("no_password_txt"));
      this->password->setFocus();
      return;
    }

  rx.setPattern(PATTERN_PASSWD);

  if (rx.indexIn(this->password->text()) < 0)
    {
      QMessageBox::information(this, tr("password_inc"),
			       tr("password_inc_txt"));
      this->password->setFocus();
      return;
    }
  this->accept();
}

void	Connect::on_cancel_clicked()
{
  this->reject();
}

void	Connect::_loadAccounts()
{
  QSqlQuery	q(Database::getInstance()->database());

  q.prepare("select username "
	    "from users;");
  q.exec();

  this->accounts->clear();
  while (q.next())
    this->accounts->addItem(q.value(0).toString());
}

// 
// Connect.cpp ends here
