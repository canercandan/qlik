//
// Socket.cpp for Socket in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Thu Jul 10 13:26:53 2008 caner candan
// Last update Tue Sep  2 14:14:36 2008 caner candan
//

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cerrno>
#include <string>
#include <iostream>
#include <sstream>
#include "Socket.h"

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
#ifdef DEBUG
      std::cout << this->head()
		<< "socket closed"
		<< std::endl;
#endif // !DEBUG
    }
}

void	Socket::send(const std::string& s)
{
  std::string	str(s);
  std::string	toSend;
  size_t	pos;

  try
    {
      if (!this->isConnected())
	throw 1;
      while ((pos = str.find('\n')) != std::string::npos)
	{
	  toSend = str.substr(0, pos + 1);
	  if (::send(this->_socket, toSend.c_str(), toSend.size(), 0) < 0)
	    throw 2;
#ifdef DEBUG
	  std::cout << this->head()
		    << "send [" << toSend << ']'
		    << std::endl;
#endif // !DEBUG
	  str = str.substr(pos + 1);
	}
    }
  catch (int e)
    {
#ifdef DEBUG
      std::cout << this->head();
      if (e == 1)
	std::cout << "send error, not connected";
      else if (e == 2)
	std::cout << "send error";
      std::cout << std::endl;
#endif // !DEBUG
    }
}

std::string	Socket::recv()
{
  char		buf[1024];
  int		size;

  try
    {
      if (!this->isConnected())
	throw 1;
      size = ::recv(this->_socket, buf, sizeof(buf), 0);
      if (!this->isGoodRecv())
	throw 2;
      if (!size)
	throw 3;
      buf[size] = 0;
#ifdef DEBUG
      std::cout << this->head()
		<< "recv [" << buf << ']'
		<< std::endl;
#endif // !DEBUG
      return (std::string(buf));
    }
  catch (int e)
    {
#ifdef DEBUG
      std::cout << this->head() << "error recv, ";
      if (e == 1)
	std::cout << "not connected";
      else if (e == 2)
	std::cout << "trame incorrect";
      else if (e == 3)
	std::cout << "trame size incorrect";
      std::cout << std::endl;
#endif // !DEBUG
      this->closeSocket();
    }
  return ("");
}

std::string	Socket::sendRecv(const std::string& s)
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

int	Socket::getSocket(void) const
{
  return (this->_socket);
}

bool	Socket::getStatus(void) const
{
  return (this->_status);
}

void	Socket::setStatus(bool status)
{
  this->_status = status;
}

std::string	Socket::head(void)
{
  std::stringstream	ss;

  ss << "Socket: [" << this->_socket << "] ";
  return (ss.str());
}
