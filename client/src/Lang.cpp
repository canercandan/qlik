// Lang.cpp --- 
// 
// Filename: Lang.cpp
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 00:57:00 2008 (+0200)
// Version: 
// Last-Updated: Thu Nov 27 00:57:03 2008 (+0200)
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

#include "Lang.h"
#include "Database.h"

Lang::Lang(QWidget* parent /*= NULL*/)
  : QDialog(parent)
{
  setupUi(this);
  language->setText(QLocale::system().name());
}

void	Lang::on_save_clicked()
{
  this->accept();
}

// 
// Lang.cpp ends here
