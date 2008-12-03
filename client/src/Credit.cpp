// Credit.cpp --- 
// 
// Filename: Credit.cpp
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 00:53:31 2008 (+0200)
// Version: 
// Last-Updated: Wed Dec  3 19:16:04 2008 (+0200)
//           By: Caner Candan
//     Update #: 11
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
#include "Credit.h"
#include "Client.h"
#include "Socket.h"
#include "Protocole.h"

Credit::Credit(QWidget* parent /*= NULL*/)
  : QDialog(parent)
{
  setupUi(this);
  reset();
}

void	Credit::reset()
{
  this->currently->setText(static_cast<Client*>
			   (this->parent())->creditCurrently->text());
}

void	Credit::on_buy_clicked()
{
  if (QMessageBox::question(this, tr("buy"), tr("buy_txt"),
			    QMessageBox::Ok | QMessageBox::Cancel)
      != QMessageBox::Ok)
    return;

  QTextStream	stream(Socket::getInstance()->socket());

  stream << ADD_CREDIT << SP << this->coins->currentText() << NL;
}

void	Credit::on_cancel_clicked()
{
  this->hide();
}

// 
// Credit.cpp ends here
