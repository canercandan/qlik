// Web.cpp --- 
// 
// Filename: Web.cpp
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Fri Nov 28 19:24:05 2008 (+0200)
// Version: 
// Last-Updated: Sat Nov 29 12:51:43 2008 (+0200)
//           By: Caner Candan
//     Update #: 12
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

#include "Web.h"

Web::Web()
  : Service(), _space(0), _nbdb(0)
{}

Web::~Web()
{}

Web::Web(const Web& web)
  : Service()
{*this = web;}

Web&	Web::operator=(const Web& web)
{
  if (this != &web)
    {
      _space = web._space;
      _nbdb = web._nbdb;
      _domain = web._domain;
    }
  return (*this);
}

// 
// Web.cpp ends here
