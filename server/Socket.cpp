//
// Socket.cpp for Socket in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Thu Jul 10 13:26:53 2008 caner candan
// Last update Sun Jul 20 11:37:22 2008 caner candan
//

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cerrno>
#include <string>
#include <iostream>
#include <sstream>
#include "Socket.h"

Socket::Socket(bool verbose /*= false*/)
  : _socket(-1), _verbose(verbose), _status(true)
{}

Socket::Socket(const Socket& s)
{*this = s;}

Socket::~Socket()
{
  closeSocket();
}

Socket&	Socket::operator=(const Socket& s)
{
  if (this != &s)
    {
      this->_socket = s._socket;
      this->_verbose = s._verbose;
      this->_status = s._status;
    }
  return (*this);
}

void	Socket::closeSocket(void)
{
  if (this->_socket >= 0)
    {
      this->setStatus(false);
      ::close(this->_socket);
      if (this->_verbose)
	std::cout << this->head()
		  << "socket closed"
		  << std::endl;
    }
}

void	Socket::send(const std::string& s,
		     bool verbose /*= false*/)
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
	  if (this->_verbose || verbose)
	    std::cout << this->head()
		      << "send [" << toSend << ']'
		      << std::endl;
	  str = str.substr(pos + 1);
	}
    }
  catch (int e)
    {
      std::cout << this->head();
      if (e == 1)
	std::cout << "send error, not connected";
      else if (e == 2)
	std::cout << "send error";
      std::cout << std::endl;
    }
}

std::string	Socket::recv(bool verbose /*= false*/)
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
      if (this->_verbose || verbose)
	std::cout << this->head()
		  << "recv [" << buf << ']'
		  << std::endl;
      return (std::string(buf));
    }
  catch (int e)
    {
      std::cout << this->head() << "error recv, ";
      if (e == 1)
	std::cout << "not connected";
      else if (e == 2)
	std::cout << "trame incorrect";
      else if (e == 3)
	std::cout << "trame size incorrect";
      std::cout << std::endl;
      this->closeSocket();
    }
  return ("");
}

std::string	Socket::sendRecv(const std::string& s,
				 bool verbose /*= false*/)
{
  this->send(s, verbose);
  return (this->recv(verbose));
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
