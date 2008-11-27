// Client.h --- 
// 
// Filename: Client.h
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 01:46:02 2008 (+0200)
// Version: 
// Last-Updated: Thu Nov 27 01:46:05 2008 (+0200)
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

#ifndef __CLIENT_H__
# define __CLIENT_H__

# include <string>
# include "Socket.h"

class	Client
{
public:
  enum	Type {SERVER, CLIENT};
public:
  Client(Socket* socket = NULL, Type type = SERVER);
  Client(const Client&);
  ~Client();
  Client&	operator=(const Client&);

public:
  Socket*	socket(void){return (_socket);}
private:
  Socket*	_socket;

public:
  bool	isConnected();

public:
  const std::string&	getBufRead(void){return (_bufread);}
  void	appendBufRead(const std::string& bufread){_bufread += bufread;}
  void	appendBufRead(const int& bufread);
  void	clearBufRead(void){_bufread.clear();}
private:
  std::string	_bufread;

public:
  const std::string&	getBufWrite(void){return (_bufwrite);}
  void	appendBufWrite(const std::string& bufwrite){_bufwrite += bufwrite;}
  void	appendBufWrite(const int& bufwrite);
  void	clearBufWrite(void){_bufwrite.clear();}
private:
  std::string	_bufwrite;

public:
  const Type&	getType(void){return (_type);}
  void	setType(const Type& type){_type = type;}
private:
  Type	_type;

public:
  const int&	getRight(void){return (_right);}
  void	setRight(const int& right){_right = right;}
private:
  int	_right;

public:
  const std::string&	getLogin(void){return (_login);}
  void	setLogin(const std::string& login){_login = login;}
private:
  std::string	_login;

public:
  const int&	getId(void){return (_id);}
  void	setId(const int& id){_id = id;}
private:
  int	_id;

public:
  const int&	getCredit(void){return (_credit);}
  void	setCredit(const int& credit){_credit = credit;}
private:
  int	_credit;
};

#endif // !__CLIENT_H__

// 
// Client.h ends here
