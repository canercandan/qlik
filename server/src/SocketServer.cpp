// SocketServer.cpp --- 
// 
// Filename: SocketServer.cpp
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 09:16:33 2008 (+0200)
// Version: 
// Last-Updated: Thu Nov 27 09:17:59 2008 (+0200)
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
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cerrno>
#include <string>
#include <iostream>
#include <sstream>
#include "SocketServer.h"
#include "State.h"
#include "Config.h"

SocketServer::SocketServer(int port)
{
  _createSocket(port);
}

void	SocketServer::_createSocket(int port)
{
  Config*	config = Config::getInstance();

  try
    {
      struct sockaddr_in	addr;
      struct protoent		*pe;

      pe = ::getprotobyname("tcp");
      if ((this->_socket = ::socket(PF_INET, SOCK_STREAM, pe->p_proto)) < 0)
	throw 1;
      addr.sin_family = AF_INET;
      addr.sin_port = ::htons(port);
      addr.sin_addr.s_addr = INADDR_ANY;
      if (bind(_socket, (struct sockaddr*)&addr, (socklen_t)sizeof(addr)) < 0)
	throw 2;
      if (listen(this->_socket, MAX_LISTEN) < 0)
	throw 3;
      if (config->isVerbose())
	std::cout << "SocketServer: [" << _socket << "] "
		  << "Socket created in localhost : "
		  << port << std::endl;
    }
  catch (int e)
    {
      if (config->isVerbose())
	{
	  std::cout << "SocketServer: [" << _socket << "] ";
	  if (e == 1)
	    std::cout << "socket error";
	  else if (e == 2)
	    std::cout << "bind error";
	  else if (e == 3)
	    std::cout << "listen error";
	  std::cout << std::endl;
	}

      State::getInstance()->setLoopState(State::LOOP_ERROR);
      this->closeSocket();
    }
}

// 
// SocketServer.cpp ends here
