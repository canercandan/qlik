//
// Client.cpp for Client in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Thu Jul 10 08:52:06 2008 caner candan
// Last update Sat Nov 15 02:22:08 2008 caner candan
//

#include <sstream>
#include "Client.h"

Client::Client(Socket* socket /*= NULL*/,
	       Type type /*= SERVER*/)
  : _socket(socket), _type(type), _right(0),
    _id(0), _credit(0)
{}

Client::Client(const Client& c)
{*this = c;}

Client::~Client()
{
  if (_socket)
    {
      delete _socket;
      _socket = NULL;
    }
}

Client&	Client::operator=(const Client& c)
{
  if (this != &c)
    {
      this->_socket = c._socket;
      this->_bufread = c._bufread;
      this->_bufwrite = c._bufwrite;
      this->_type = c._type;
      this->_right = c._right;
      this->_login = c._login;
      this->_id = c._id;
      this->_credit = c._credit;
    }
  return (*this);
}

bool	Client::isConnected()
{
  return (!_login.empty() && _socket->getStatus());
}

void	Client::appendBufRead(const int& bufread)
{
  std::stringstream	ss;

  ss << bufread;
  this->appendBufRead(ss.str());
}

void	Client::appendBufWrite(const int& bufwrite)
{
  std::stringstream	ss;

  ss << bufwrite;
  this->appendBufWrite(ss.str());
}
