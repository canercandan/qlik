//
// Database.cpp for server in /home/candan_c/cu/rendu/qlik/server/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sat Oct 25 21:11:08 2008 caner candan
// Last update Sat Oct 25 21:56:24 2008 caner candan
//

#include "Database.h"
#include "Config.h"

Database::Database()
{
  _db.Open(Config::getInstance()->getDatabase());
}

Database::~Database()
{}

SQLiteWrapper&	Database::operator*()
{
  return (_db);
}

SQLiteWrapper&	Database::database()
{
  return (_db);
}
