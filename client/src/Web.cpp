// Web.cpp --- 
// 
// Filename: Web.cpp
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 01:05:29 2008 (+0200)
// Version: 
// Last-Updated: Sat Nov 29 18:10:01 2008 (+0200)
//           By: Caner Candan
//     Update #: 13
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

#include <QTextStream>
#include <QMessageBox>
#include "Web.h"
#include "Socket.h"
#include "Protocole.h"

Web::Web(QWidget* parent /*= NULL*/)
  : QDialog(parent)
{
  setupUi(this);
}

void	Web::on_start_clicked()
{
  QMessageBox::information(this, tr("not_yet"), tr("not_yet_txt"));
}

void	Web::on_stop_clicked()
{
  QMessageBox::information(this, tr("not_yet"), tr("not_yet_txt"));
}

void	Web::on_renew_clicked()
{
  if (QMessageBox::question(this, tr("renew"), tr("renew_txt"),
			    QMessageBox::Ok | QMessageBox::Cancel)
      != QMessageBox::Ok)
    return;

  QTextStream	stream(Socket::getInstance()->socket());

  stream << RENEW_WEB << SP << this->name->text() << NL;
}

// 
// Web.cpp ends here
