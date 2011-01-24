// About.h --- 
// 
// Filename: About.h
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Wed Nov 26 23:21:38 2008 (+0200)
// Version: 
// Last-Updated: Mon Dec  8 18:18:59 2008 (+0200)
//           By: Caner Candan
//     Update #: 7
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

#ifndef __ABOUT_H__
# define __ABOUT_H__

# include <QDialog>
# include "Singleton.hpp"
# include "ui_About.h"

class	About : public QDialog, public Singleton<About>,
		public Ui::About
{
  Q_OBJECT

  friend class	Singleton<About>;
private slots:
  void	on_close_clicked();
private:
  About(QWidget* parent = NULL);
};

#endif // !__ABOUT_H__

// 
// About.h ends here
