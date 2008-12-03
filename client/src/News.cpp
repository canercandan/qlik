// News.cpp --- 
// 
// Filename: News.cpp
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 00:57:34 2008 (+0200)
// Version: 
// Last-Updated: Thu Dec  4 00:21:57 2008 (+0200)
//           By: Caner Candan
//     Update #: 4
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

#include "News.h"
#include "Client.h"
#include "Socket.h"
#include "Protocole.h"

News::News(QWidget* parent /*= NULL*/)
  : QDialog(parent)
{
  setupUi(this);

  Client*	client = static_cast<Client*>(parent);
  bool		rightAdmin =
    ((client->getRight() & RIGHT_ADMIN) == RIGHT_ADMIN);

  addSubject->setEnabled(rightAdmin);
  addBody->setEnabled(rightAdmin);
  addOk->setEnabled(rightAdmin);
}

void	News::on_readClose_clicked()
{
  this->hide();
}

void	News::on_addOk_clicked()
{
  QTextStream	stream(Socket::getInstance()->socket());

  stream << NEWS_ADD
	 << SP << this->addSubject->text()
	 << SP << this->addBody->toPlainText()
	 << NL;
}

void	News::on_addCancel_clicked()
{
  this->hide();
}

// 
// News.cpp ends here
