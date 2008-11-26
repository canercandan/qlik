// State.h --- 
// 
// Filename: State.h
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 01:05:14 2008 (+0200)
// Version: 
// Last-Updated: Thu Nov 27 01:05:16 2008 (+0200)
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

#ifndef __STATE_H__
# define __STATE_H__

# include "Singleton.hpp"

class	State : public Singleton<State>
{
  friend class	Singleton<State>;
public:
  enum	List {DONE, WAIT};

private:
  State();

public:
  const List&	getWebList(void){return (_weblist);}
  void	setWebList(const List& weblist){_weblist = weblist;}
private:
  List	_weblist;

public:
  const List&	getStreamList(void){return (_streamlist);}
  void	setStreamList(const List& streamlist){_streamlist = streamlist;}
private:
  List	_streamlist;
};

#endif // !__STATE_H__

// 
// State.h ends here
