// Signal.h --- 
// 
// Filename: Signal.h
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 09:15:58 2008 (+0200)
// Version: 
// Last-Updated: Thu Nov 27 09:16:01 2008 (+0200)
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

#ifndef __SIGNAL_H__
# define __SIGNAL_H__

# include <list>
# include <map>
# include "Singleton.hpp"
# include "ISignalManager.h"

class	Signal : public Singleton<Signal>
{
  friend class	Singleton<Signal>;
public:
  enum	Type {INT, TERM};
  enum	Priority {HIGH, NORMAL, LOW};

  typedef std::pair<ISignalManager*, ISignalManager::callback>	pairCallback;
  typedef std::list<pairCallback>				listCallback;
  typedef std::map<Priority, listCallback>			mapPriority;
  typedef std::map<Type, mapPriority>				mapSignal;

  void	addCallback(const Type&, const Priority&,
		    ISignalManager*, ISignalManager::callback);
private:
  Signal();
  ~Signal();

  static void	_sigInt(int);
  static void	_sigTerm(int);

  void	_signalLoop(const Type&);
  void	_signalLoopPriority(const Type&, const Priority&);
private:
  mapSignal	_signals;
};

#endif // !__SIGNAL_H__

// 
// Signal.h ends here
