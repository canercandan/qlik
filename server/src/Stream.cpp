// Stream.cpp --- 
// 
// Filename: Stream.cpp
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 09:18:15 2008 (+0200)
// Version: 
// Last-Updated: Thu Nov 27 09:20:12 2008 (+0200)
//           By: Caner Candan
//     Update #: 2
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
// Floor, Boston, MA 02110-1301, USA.#include "Stream.h"

// 
// 

// Code:

#include "Stream.h"

Stream::Stream()
{}

Stream::~Stream()
{}

Stream::Stream(const Stream& stream)
{*this = stream;}

Stream&	Stream::operator=(const Stream& stream)
{
  if (this != &stream)
    {
      _name = stream._name;
      _slots = stream._slots;
      _bits = stream._bits;
      _title = stream._title;
      _port = stream._port;
    }
  return (*this);
}

// 
// Stream.cpp ends here
