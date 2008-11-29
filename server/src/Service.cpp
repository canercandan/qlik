// Service.cpp --- 
// 
// Filename: Service.cpp
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Sat Nov 29 10:15:07 2008 (+0200)
// Version: 
// Last-Updated: Sat Nov 29 10:16:51 2008 (+0200)
//           By: Caner Candan
//     Update #: 5
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

#include "Service.h"

Service::Service()
  : _created(0), _expired(0), _price(0)
{}

Service::~Service()
{}

Service::Service(const Service& service)
{*this = service;}

Service&	Service::operator=(const Service& service)
{
  if (this != &service)
    {
      _login = service._login;
      _name = service._name;
      _created = service._created;
      _expired = service._expired;
      _price = service._price;
    }
  return (*this);
}

// 
// Service.cpp ends here
