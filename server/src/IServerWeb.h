// IServerWeb.h --- 
// 
// Filename: IServerWeb.h
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 09:11:59 2008 (+0200)
// Version: 
// Last-Updated: Thu Nov 27 09:12:02 2008 (+0200)
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

#ifndef __ISERVERWEB_H__
# define __ISERVERWEB_H__

# include <string>

class	IServerWeb
{
public:
  virtual ~IServerWeb(){}

  virtual void	createHost(const std::string& domain) = 0;
};

#endif // !__ISERVERWEB_H__

// 
// IServerWeb.h ends here
