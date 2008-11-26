// Service.h --- 
// 
// Filename: Service.h
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 01:03:35 2008 (+0200)
// Version: 
// Last-Updated: Thu Nov 27 01:03:39 2008 (+0200)
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

#ifndef __SERVICE_H__
# define __SERVICE_H__

# include <QDialog>
# include "Singleton.hpp"
# include "ui_Service.h"

class	Service : public QDialog, public Singleton<Service>,
		  public Ui::Service
{
  Q_OBJECT

  friend class	Singleton<Service>;
public:
  void	createWebOffer();
  void	createStreamOffer();
  void	createWebMore();
  void	createStreamMore();
private slots:
  void	on_ok_clicked();
  void	on_cancel_clicked();
private:
  Service(QWidget* parent = NULL);

  bool	_confirmOffer(QListWidget*);
  bool	_confirmMore(QComboBox* list1, int ratio1,
		     QComboBox* list2, int ratio2);
};

#endif // !__SERVICE_H__

// 
// Service.h ends here
