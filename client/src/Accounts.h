// Accounts.h --- 
// 
// Filename: Accounts.h
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Wed Nov 26 23:23:35 2008 (+0200)
// Version: 
// Last-Updated: Wed Nov 26 23:23:42 2008 (+0200)
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

#ifndef __ACCOUNTS_H__
# define __ACCOUNTS_H__

# include <QDialog>
# include "Singleton.hpp"
# include "ui_Accounts.h"

class	Accounts : public QDialog, public Singleton<Accounts>,
		   public Ui::Accounts
{
  Q_OBJECT

  friend class	Singleton<Accounts>;
public:
  void	reset();
private slots:
  void	on_save_clicked();
  void	on_done_clicked();
  void	on_manage_clicked();
  void	on_add_clicked();
  void	on_del_clicked();

  void	_modifyPassword(int);
private:
  Accounts(QWidget* parent = NULL);

  void	_loadList();
  void	_loadAccount();
  void	_resetAccount();
};

#endif // !__ACCOUNTS_H__

// 
// Accounts.h ends here
