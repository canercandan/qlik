// Stream.h --- 
// 
// Filename: Stream.h
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 09:18:19 2008 (+0200)
// Version: 
// Last-Updated: Thu Nov 27 09:18:22 2008 (+0200)
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

#ifndef __STREAM_H__
# define __STREAM_H__

# include <string>

class	Stream
{
public:
  Stream();
  ~Stream();
  Stream(const Stream&);
  Stream&	operator=(const Stream&);
public:
  const std::string&	getLogin(void){return (_login);}
  void	setLogin(const std::string& login){_login = login;}
private:
  std::string	_login;
public:
  const std::string&	getName(void){return (_name);}
  void	setName(const std::string& name){_name = name;}
private:
  std::string	_name;
public:
  const int&	getSlots(void){return (_slots);}
  void	setSlots(const int& slots){_slots = slots;}
private:
  int	_slots;
public:
  const int&	getBits(void){return (_bits);}
  void	setBits(const int& bits){_bits = bits;}
private:
  int	_bits;
public:
  const std::string&	getTitle(void){return (_title);}
  void	setTitle(const std::string& title){_title = title;}
private:
  std::string	_title;
public:
  const int&	getPort(void){return (_port);}
  void	setPort(const int& port){_port = port;}
private:
  int	_port;
};

#endif // !__STREAM_H__

// 
// Stream.h ends here
