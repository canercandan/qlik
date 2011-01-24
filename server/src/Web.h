// Web.h --- 
// 
// Filename: Web.h
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Fri Nov 28 19:21:53 2008 (+0200)
// Version: 
// Last-Updated: Sat Nov 29 10:15:03 2008 (+0200)
//           By: Caner Candan
//     Update #: 11
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

# include <string>
# include "Service.h"

class	Web : public Service
{
public:
  Web();
  ~Web();
  Web(const Web&);
  Web&	operator=(const Web&);

public:
  const int&	getSpace(void){return (_space);}
  void	setSpace(const int& space){_space = space;}
private:
  int	_space;

public:
  const int&	getNbDb(void){return (_nbdb);}
  void	setNbDb(const int& nbdb){_nbdb = nbdb;}
private:
  int	_nbdb;

public:
  const std::string&	getDomain(void){return (_domain);}
  void	setDomain(const std::string& domain){_domain = domain;}
private:
  std::string	_domain;
};

#endif // !__WEB_H__


// 
// Web.h ends here
