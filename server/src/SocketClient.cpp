// SocketClient.cpp --- 
// 
// Filename: SocketClient.cpp
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 09:16:21 2008 (+0200)
// Version: 
// Last-Updated: Thu Nov 27 09:16:24 2008 (+0200)
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

#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <sstream>
#include "SocketClient.h"
#include "State.h"
#include "Config.h"

SocketClient::SocketClient(int socket)
{
  _acceptClient(socket);
}

void	SocketClient::_acceptClient(int socket)
{
  Config*	config = Config::getInstance();

  try
    {
      if ((this->_socket = accept(socket, NULL, NULL)) < 0)
	throw true;
    }
  catch (bool)
    {
      if (config->isVerbose())
	std::cout << "SocketClient: [" << _socket << "] "
		  << "accept error"
		  << std::endl;

      State::getInstance()->setLoopState(State::LOOP_ERROR);
      this->closeSocket();
    }
}

// 
// SocketClient.cpp ends here
