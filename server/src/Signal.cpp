// Signal.cpp --- 
// 
// Filename: Signal.cpp
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 09:15:54 2008 (+0200)
// Version: 
// Last-Updated: Thu Nov 27 09:15:56 2008 (+0200)
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

#include <iostream>
#include <csignal>
#include "Signal.h"

Signal::Signal()
{
  ::signal(SIGINT, _sigInt);
  ::signal(SIGTERM, _sigTerm);
}

Signal::~Signal()
{}

void	Signal::addCallback(const Signal::Type& type, const Signal::Priority& priority,
			    ISignalManager* sm, ISignalManager::callback callback)
{
  _signals[type][priority].push_back(pairCallback(sm, callback));
}

void	Signal::_sigInt(int)
{
  Signal::getInstance()->_signalLoop(INT);
}

void	Signal::_sigTerm(int)
{
  Signal::getInstance()->_signalLoop(TERM);
}

void	Signal::_signalLoop(const Type& type)
{
  _signalLoopPriority(type, HIGH);
  _signalLoopPriority(type, NORMAL);
  _signalLoopPriority(type, LOW);

  //::exit(-1);
}

void	Signal::_signalLoopPriority(const Type& type,
				    const Priority& priority)
{
  mapPriority&	map = _signals[type];
  listCallback&	list = map[priority];

  for (listCallback::const_iterator
	 it = list.begin(),
	 end = list.end();
       it != end; ++it)
    {
      ISignalManager*		sm = it->first;
      ISignalManager::callback	cb = it->second;

      (sm->*cb)();
    }
}

// 
// Signal.cpp ends here
