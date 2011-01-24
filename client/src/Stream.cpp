// Stream.cpp --- 
// 
// Filename: Stream.cpp
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 01:05:20 2008 (+0200)
// Version: 
// Last-Updated: Sat Nov 29 13:16:49 2008 (+0200)
//           By: Caner Candan
//     Update #: 21
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
#include "Stream.h"
#include "Socket.h"
#include "Protocole.h"

Stream::Stream(QWidget* parent /*= NULL*/)
  : QDialog(parent)
{
  setupUi(this);
}

void	Stream::on_start_clicked()
{
  QTextStream	stream(Socket::getInstance()->socket());

  stream << STREAM_START << SP << this->name->text() << NL;
}

void	Stream::on_stop_clicked()
{
  QTextStream	stream(Socket::getInstance()->socket());

  stream << STREAM_STOP << SP << this->name->text() << NL;
}

void	Stream::on_renew_clicked()
{
  if (QMessageBox::question(this, tr("renew"), tr("renew_txt"),
			    QMessageBox::Ok | QMessageBox::Cancel)
      != QMessageBox::Ok)
    return;

  QTextStream	stream(Socket::getInstance()->socket());

  stream << RENEW_STREAM << SP << this->name->text() << NL;
}

// 
// Stream.cpp ends here
