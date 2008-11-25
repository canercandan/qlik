//
// Credit.cpp for server in /home/candan_c/cu/rendu/qlik/server/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sat Oct 25 21:03:17 2008 caner candan
// Last update Tue Nov 18 11:36:38 2008 caner candan
//

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
