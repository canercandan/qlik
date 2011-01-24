// Credit.cpp --- 
// 
// Filename: Credit.cpp
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 09:09:52 2008 (+0200)
// Version: 
// Last-Updated: Thu Nov 27 09:09:55 2008 (+0200)
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

#include "Credit.h"
#include "Database.h"

Credit::Credit(Client* client)
  : _client(client)
{}

void	Credit::add(const int& value)
{
  Database*		database = Database::getInstance();
  SQLiteStatement*	stmt =
    database->database().Statement("update users "
				   "set credit = credit + ? "
				   "where id = ?;");

  stmt->Bind(0, value);
  stmt->Bind(1, _client->getId());

  stmt->Execute();

  _client->setCredit(_client->getCredit() + value);
}

void	Credit::sub(const int& value)
{
  Database*		database = Database::getInstance();
  SQLiteStatement*	stmt =
    database->database().Statement("update users "
				   "set credit = credit - ? "
				   "where id = ?;");

  stmt->Bind(0, value);
  stmt->Bind(1, _client->getId());

  stmt->Execute();

  _client->setCredit(_client->getCredit() - value);
}

bool	Credit::haveEnoughFor(const int& value)
{
  Database*		database = Database::getInstance();
  SQLiteStatement*	stmt =
    database->database().Statement("select credit "
				   "from users "
				   "where id = ?;");

  stmt->Bind(0, _client->getId());

  bool	ret = stmt->NextRow();

  if (!ret)
    {
      stmt->End();
      return (false);
    }

  int	res = stmt->ValueInt(0);

  stmt->End();

  return (res >= value);
}

// 
// Credit.cpp ends here
