//
// Client.cpp for Client in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Thu Jul 10 08:52:06 2008 caner candan
// Last update Sun Aug  3 14:05:04 2008 caner candan
//

#include "Client.h"

Client::Client(Socket *socket /*= NULL*/,
	       Type type /*= SERVER*/)
  : _socket(socket), _type(type), _right(USER),
    _id(0), _credit(0)
{}

Client::Client(const Client& c)
{*this = c;}

Client::~Client()
{}

Client&	Client::operator=(const Client& c)
{
  if (this != &c)
    {
      this->_socket = c._socket;
      this->_bufRead = c._bufRead;
      this->_bufWrite = c._bufWrite;
      this->_type = c._type;
      this->_right = c._right;
      this->_login = c._login;
      this->_id = c._id;
      this->_credit = c._credit;
    }
  return (*this);
}

Socket	*Client::getSocket(void) const
{
  return (this->_socket);
}

const std::string&	Client::getBufRead(void) const
{
  return (this->_bufRead);
}

const std::string&	Client::getBufWrite(void) const
{
  return (this->_bufWrite);
}

const Client::Type&	Client::getType(void) const
{
  return (this->_type);
}

const Client::Right&	Client::getRight(void) const
{
  return (this->_right);
}

const std::string&	Client::getLogin(void) const
{
  return (this->_login);
}

int	Client::getId(void) const
{
  return (this->_id);
}

int	Client::getCredit(void) const
{
  return (this->_credit);
}

bool	Client::isConnected() const
{
  return (!this->getLogin().empty()
	  && this->getSocket()->getStatus());
}

void	Client::setBufRead(const std::string& bufRead)
{
  this->_bufRead += bufRead;
}

void	Client::setBufWrite(const std::string& bufWrite)
{
  this->_bufWrite += bufWrite;
}

void	Client::setLogin(const std::string& login)
{
  this->_login = login;
}

void	Client::setId(int id)
{
  this->_id = id;
}

void	Client::setCredit(int credit)
{
  this->_credit = credit;
}

void	Client::clearBufRead(void)
{
  if (!this->_bufRead.empty())
    this->_bufRead.clear();
}

void	Client::clearBufWrite(void)
{
  if (!this->_bufWrite.empty())
    this->_bufWrite.clear();
}
