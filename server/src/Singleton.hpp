// Singleton.hpp --- 
// 
// Filename: Singleton.hpp
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 09:16:02 2008 (+0200)
// Version: 
// Last-Updated: Sat Nov 29 12:31:08 2008 (+0200)
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
// 27-Nov-2008    Caner Candan  
//    Last-Updated: Thu Nov 27 15:17:52 2008 (+0200) #6 (Caner Candan)
//    delete getInstance overloaded with a string param
// 27-Nov-2008    Caner Candan  
//    Last-Updated: Thu Nov 27 14:12:23 2008 (+0200) #4 (Caner Candan)
//    add a getInstance with string param
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

#ifndef __SINGLETON_H__
# define __SINGLETON_H__

# include <cstdlib>
# include <string>

template <typename T>
class	Singleton
{
protected:
  Singleton(){}
  ~Singleton(){}
public:
  static T*	getInstance()
  {
    if (!_singleton)
      _singleton = new T;
    return (static_cast<T*>(_singleton));
  }

  static void	kill()
  {
    if (_singleton)
      {
	delete _singleton;
	_singleton = NULL;
      }
  }

  static bool	exist(){return (_singleton != NULL);}
private:
  static T*	_singleton;
};

template <typename T>
T*	Singleton<T>::_singleton = NULL;

#endif // !__SINGLETON_H__

// 
// Singleton.hpp ends here
