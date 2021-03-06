// Stream.h --- 
// 
// Filename: Stream.h
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 01:05:25 2008 (+0200)
// Version: 
// Last-Updated: Fri Nov 28 23:21:10 2008 (+0200)
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

#ifndef __STREAM_H__
# define __STREAM_H__

# include <QDialog>
# include "Singleton.hpp"
# include "ui_Stream.h"

class	Stream : public QDialog, public Singleton<Stream>,
		 public Ui::Stream
{
  Q_OBJECT

  friend class	Singleton<Stream>;
private slots:
  void	on_start_clicked();
  void	on_stop_clicked();
  void	on_renew_clicked();
private:
  Stream(QWidget* parent = NULL);
};

#endif // !__STREAM_H__

// 
// Stream.h ends here
