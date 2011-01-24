// AccountsAdmin.h --- 
// 
// Filename: AccountsAdmin.h
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Wed Nov 26 23:24:03 2008 (+0200)
// Version: 
// Last-Updated: Wed Nov 26 23:25:22 2008 (+0200)
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

#ifndef __ACCOUNTSADMIN_H__
# define __ACCOUNTSADMIN_H__

# include <QDialog>
# include "Singleton.hpp"
# include "ui_AccountsAdmin.h"

class	AccountsAdmin : public QDialog, public Singleton<AccountsAdmin>,
			public Ui::AccountsAdmin
{
  Q_OBJECT

  friend class	Singleton<AccountsAdmin>;
private slots:
  void	on_minus_clicked();
  void	on_plus_clicked();

  void	on_ok_clicked();
  void	on_cancel_clicked();
private:
  AccountsAdmin(QWidget* parent = NULL);
};

#endif // !__ACCOUNTSADMIN_H__

// 
// AccountsAdmin.h ends here
