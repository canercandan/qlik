// Socket.h --- 
// 
// Filename: Socket.h
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 01:05:04 2008 (+0200)
// Version: 
// Last-Updated: Thu Nov 27 01:05:07 2008 (+0200)
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

#ifndef __SOCKET_H__
# define __SOCKET_H__

# include <QtNetwork>
# include "Singleton.hpp"

class	Socket : public Singleton<Socket>
{
  friend class	Singleton<Socket>;
public:
  QTcpSocket*	socket();

  void	connect(const QString& host,
		const int& port);
  void	close();
private:
  Socket();
  ~Socket();
private:
  QTcpSocket*	_socket;
};

#endif // !__SOCKET_H__

// 
// Socket.h ends here
