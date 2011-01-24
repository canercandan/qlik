// State.cpp --- 
// 
// Filename: State.cpp
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 01:05:09 2008 (+0200)
// Version: 
// Last-Updated: Wed Dec  3 01:32:44 2008 (+0200)
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
// Floor, Boston, MA 02110-1301, USA.

// 
// 

// Code:

#include "State.h"

State::State()
  : _weblist(WAIT), _streamlist(WAIT), _clientslist(WAIT),
    _accountslist(WAIT), _creditlist(WAIT), _offerweblist(WAIT),
    _offerstreamlist(WAIT), _newslist(WAIT)
{}

// 
// State.cpp ends here
