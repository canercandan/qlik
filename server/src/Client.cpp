// Client.cpp --- 
// 
// Filename: Client.cpp
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 01:45:57 2008 (+0200)
// Version: 
// Last-Updated: Wed Dec  3 17:53:53 2008 (+0200)
//           By: Caner Candan
//     Update #: 21
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

#include <sstream>
#include "Client.h"
#include "Database.h"

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

void	Client::syncCredit()
{
  Database*		database = Database::getInstance();
  SQLiteStatement*	stmt =
    database->database().Statement("select credit "
				   "from users "
				   "where id = ?;");

  stmt->Bind(0, this->getId());

  if (!stmt->NextRow())
    {
      stmt->End();
      return;
    }

  int	credit = stmt->ValueInt(0);

  stmt->End();

  if (this->getCredit() == credit)
    return;

  this->setCredit(credit);
}

void	Client::syncRight()
{
  Database*		database = Database::getInstance();
  SQLiteStatement*	stmt =
    database->database().Statement("select right "
				   "from users "
				   "where id = ?;");

  stmt->Bind(0, this->getId());

  if (!stmt->NextRow())
    {
      stmt->End();
      return;
    }

  int	right = stmt->ValueInt(0);

  stmt->End();

  if (this->getRight() == right)
    return;

  this->setRight(right);
}

// 
// Client.cpp ends here
