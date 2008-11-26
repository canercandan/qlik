// Options.h --- 
// 
// Filename: Options.h
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 01:03:20 2008 (+0200)
// Version: 
// Last-Updated: Thu Nov 27 01:03:23 2008 (+0200)
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

#ifndef __OPTIONS_H__
# define __OPTIONS_H__

# include <QDialog>
# include "Singleton.hpp"
# include "ui_Options.h"

# define OPT_VERBOSE	1 << 1
# define OPT_SECURE	1 << 2
# define OPT_SPLASH	1 << 3

class	Options : public QDialog, public Singleton<Options>,
		  public Ui::Options
{
  Q_OBJECT

  friend class	Singleton<Options>;
private slots:
  void	on_reconnect_clicked();
  void	on_save_clicked();
  void	on_cancel_clicked();
private:
  Options(QWidget* parent = NULL);

  void	_connectToSocket();
  void	_fillFields();
  void	_modifyServer();
};

#endif // !__OPTIONS_H__

// 
// Options.h ends here
