// Create.h --- 
// 
// Filename: Create.h
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 00:51:51 2008 (+0200)
// Version: 
// Last-Updated: Thu Nov 27 00:53:03 2008 (+0200)
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

#ifndef __CREATE_H__
# define __CREATE_H__

# include <QDialog>
# include "ui_Create.h"

class	Create : public QDialog, public Ui::Create
{
  Q_OBJECT

  public:
  Create(QWidget *parent = NULL);
  ~Create();
private slots:
  void	on_ok_clicked();
  void	on_cancel_clicked();
private:
};

#endif // !__CREATE_H__

// 
// Create.h ends here
