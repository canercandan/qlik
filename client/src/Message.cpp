// Message.cpp --- 
// 
// Filename: Message.cpp
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 00:57:21 2008 (+0200)
// Version: 
// Last-Updated: Thu Nov 27 00:57:24 2008 (+0200)
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

#include <QWidget>
#include <QMessageBox>
#include "Message.h"
#include "Client.h"
#include "Socket.h"
#include "Contact.h"
#include "Protocole.h"

Message::Message(QWidget* parent /*= NULL*/)
  : QDialog(parent)
{
  setupUi(this);
}

void	Message::on_send_clicked()
{
  QTextStream		stream(Socket::getInstance()->socket());
  const QString&	from = this->from->text();
  const QString&	to = this->to->text();
  const QString&	edit = this->edit->text();

  if (edit.isEmpty())
    return;

  stream << MESSAGE << SP << to << SP << edit << NL;

  static_cast<Client*>(this->parent())->appendMessage(to, from, edit);

  this->edit->clear();
  this->edit->setFocus();
}

void	Message::on_add_clicked()
{
  Contact	contact;

  contact.username->setText(this->to->text());
  contact.alias->setFocus();

  if (contact.exec() != QDialog::Accepted)
    return;

  static_cast<Client*>(this->parent())->addToContactsList(contact);
}

// 
// Message.cpp ends here
