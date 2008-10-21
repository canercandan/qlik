//
// Database.cpp for Database in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Aug 17 12:27:49 2008 caner candan
// Last update Sun Oct 12 17:19:42 2008 caner candan
//

#include "Database.h"

Database::Database()
{}

Database::~Database()
{
  close();
}

const QSqlDatabase&	Database::database()
{
  return (this->_db);
}

bool	Database::connect()
{
  this->_db = QSqlDatabase::addDatabase("QSQLITE");
  this->_db.setDatabaseName(DBFILE);
  return (this->_db.open());
}

void	Database::close()
{
  this->_db.close();
}
