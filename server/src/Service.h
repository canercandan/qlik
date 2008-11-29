// Service.h --- 
// 
// Filename: Service.h
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Sat Nov 29 10:09:00 2008 (+0200)
// Version: 
// Last-Updated: Sat Nov 29 11:26:34 2008 (+0200)
//           By: Caner Candan
//     Update #: 8
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

# include <string>

class	Service
{
public:
  Service();
  ~Service();
  Service(const Service&);
  Service&	operator=(const Service&);

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
  const int&	getCreated(void){return (_created);}
  void	setCreated(const int& created){_created = created;}
private:
  int	_created;

public:
  const int&	getExpired(void){return (_expired);}
  void	setExpired(const int& expired){_expired = expired;}
private:
  int	_expired;

public:
  const int&	getPrice(void){return (_price);}
  void	setPrice(const int& price){_price = price;}
private:
  int	_price;
};

#endif // !__SERVICE_H__

// 
// Service.h ends here
