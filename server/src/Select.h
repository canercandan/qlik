// Select.h --- 
// 
// Filename: Select.h
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 09:14:17 2008 (+0200)
// Version: 
// Last-Updated: Thu Nov 27 09:14:20 2008 (+0200)
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

#ifndef __SELECT_H__
# define __SELECT_H__

# include <string>
# include "Client.h"
# include "Server.h"
# include "ISignalManager.h"

class	Select : public ISignalManager
{
public:
  Select(Server*);
  ~Select();

  void	start();

  void	signal();
private:
  void	_addServer(int port);
  void	_addClient(Client* server);

  void	_setFd(fd_set& fdRead, fd_set& fdWrite, int& fdMax);
  void	_issetFd(fd_set& fdRead, fd_set& fdWrite);

  void	_serverRead(Client* server);

  void	_clientRead(Client* client);
  void	_clientWrite(Client* client);
private:
  Server*	_server;
};

#endif // !__SELECT_H__

// 
// Select.h ends here
