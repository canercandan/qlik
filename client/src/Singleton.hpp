// Singleton.hpp --- 
// 
// Filename: Singleton.hpp
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 01:03:43 2008 (+0200)
// Version: 
// Last-Updated: Thu Nov 27 01:03:46 2008 (+0200)
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

#ifndef __SINGLETON_HPP__
# define __SINGLETON_HPP__

# include <cstdlib>
# include <QWidget>

template <typename T>
class	Singleton
{
public:
  static T*	getInstance()
  {
    if (!_singleton)
      _singleton = new T;
    return (static_cast<T*>(_singleton));
  }

  static T*	getInstance(QWidget* parent)
  {
    if (!_singleton)
      _singleton = new T(parent);
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

  static bool	exist()
  {
    return (_singleton);
  }
protected:
  Singleton(){}
  ~Singleton(){}
private:
  static T*	_singleton;
};

template <typename T>
T*	Singleton<T>::_singleton = NULL;

#endif // !__SINGLETON_HPP__

// 
// Singleton.hpp ends here
