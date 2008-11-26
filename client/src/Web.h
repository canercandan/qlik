// Web.h --- 
// 
// Filename: Web.h
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 01:05:34 2008 (+0200)
// Version: 
// Last-Updated: Thu Nov 27 01:05:37 2008 (+0200)
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

#ifndef __WEB_H__
# define __WEB_H__

# include <QDialog>
# include "Singleton.hpp"
# include "ui_Web.h"

class	Web : public QDialog, public Singleton<Web>,
	      public Ui::Web
{
  Q_OBJECT

  friend class	Singleton<Web>;
private slots:
private:
  Web(QWidget* parent = NULL);
};

#endif // !__WEB_H__

// 
// Web.h ends here
