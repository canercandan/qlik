// Socket.cpp --- 
// 
// Filename: Socket.cpp
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 09:16:06 2008 (+0200)
// Version: 
// Last-Updated: Thu Nov 27 09:16:09 2008 (+0200)
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
#include <unistd.h>
#include <cerrno>
#include <string>
#include <iostream>
#include <sstream>
#include "Socket.h"
#include "Config.h"

Socket::Socket()
  : _socket(-1), _status(true)
{}

Socket::~Socket()
{
  closeSocket();
}

void	Socket::closeSocket(void)
{
  if (this->_socket >= 0)
    {
      this->setStatus(false);
      ::close(this->_socket);
      if (Config::getInstance()->isVerbose())
	std::cout << "Socket: [" << _socket
		  << "] socket closed" << std::endl;
    }
}

void	Socket::send(std::string s)
{
  Config*	config = Config::getInstance();

  try
    {
      std::string	str(s);
      std::string	toSend;
      size_t		pos;

      if (!this->isConnected())
	throw 1;
      while ((pos = str.find('\n')) != std::string::npos)
	{
	  toSend = str.substr(0, pos + 1);
	  if (::send(this->_socket, toSend.c_str(), toSend.size(), 0) < 0)
	    throw 2;
	  if (config->isVerbose())
	    std::cout << "Socket: [" << _socket
		      << "] send [" << toSend << ']' << std::endl;
	  str = str.substr(pos + 1);
	}
    }
  catch (int e)
    {
      if (config->isVerbose())
	{
	  std::cout << "Socket: [" << _socket << "] ";
	  if (e == 1)
	    std::cout << "send error, not connected";
	  else if (e == 2)
	    std::cout << "send error";
	  std::cout << std::endl;
	}
    }
}

std::string	Socket::recv()
{
  Config*	config = Config::getInstance();

  try
    {
      if (!this->isConnected())
	throw 1;

      char	buf[1024];
      int	size = ::recv(_socket, buf, sizeof(buf), 0);

      if (!this->isGoodRecv())
	throw 2;
      if (!size)
	throw 3;
      buf[size] = 0;
      if (config->isVerbose())
	std::cout << "Socket: [" << _socket
		  << "] recv [" << buf << ']' << std::endl;
      return (std::string(buf));
    }
  catch (int e)
    {
      if (config->isVerbose())
	{
	  std::cout << "Socket: [" << _socket << "] error recv, ";
	  if (e == 1)
	    std::cout << "not connected";
	  else if (e == 2)
	    std::cout << "trame incorrect";
	  else if (e == 3)
	    std::cout << "trame size incorrect";
	  std::cout << std::endl;
	}
      this->closeSocket();
    }
  return ("");
}

std::string	Socket::sendRecv(std::string s)
{
  this->send(s);
  return (this->recv());
}

bool	Socket::isConnected(void) const
{
  return (this->_socket >= 0);
}

bool	Socket::isGoodRecv(void) const
{
  return (errno != EAGAIN);
}

// 
// Socket.cpp ends here
