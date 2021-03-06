// Apache.h --- 
// 
// Filename: Apache.h
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 01:44:29 2008 (+0200)
// Version: 
// Last-Updated: Thu Nov 27 01:45:53 2008 (+0200)
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

#ifndef __APACHE_H__
# define __APACHE_H__

# include "IServerWeb.h"
# include "Client.h"

class	Apache : public IServerWeb
{
public:
  Apache(Client*);

  void	createHost(const std::string& domain);
private:
  void	_createRoot();
private:
  std::string	_user;
  std::string	_dirConfig;
  std::string	_dirUserConfig;
  std::string	_fileUserConfig;
  std::string	_rootDir;
};

#endif // !__APACHE_H__

// 
// Apache.h ends here
