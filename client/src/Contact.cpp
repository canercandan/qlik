// Contact.cpp --- 
// 
// Filename: Contact.cpp
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 00:51:30 2008 (+0200)
// Version: 
// Last-Updated: Wed Dec  3 20:09:58 2008 (+0200)
//           By: Caner Candan
//     Update #: 3
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

#include <QWidget>
#include <QMessageBox>
#include "Contact.h"
#include "Protocole.h"

Contact::Contact(QWidget* parent /*= NULL*/)
  : QDialog(parent)
{
  setupUi(this);
}

void	Contact::on_ok_clicked()
{
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
  if (!this->alias->text().isEmpty())
    {
      rx.setPattern(PATTERN_USERNAME);
      if (rx.indexIn(this->alias->text()) < 0)
	{
	  QMessageBox::information(this, tr("alias_inc"), tr("alias_inc_txt"));
	  this->alias->setFocus();
	  return;
	}
    }
  this->accept();
}

void	Contact::on_cancel_clicked()
{
  this->reject();
}

// 
// Contact.cpp ends here
