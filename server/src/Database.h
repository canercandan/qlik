//
// Database.h for server in /home/candan_c/cu/rendu/qlik/server/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sat Oct 25 21:07:10 2008 caner candan
// Last update Sat Oct 25 21:58:12 2008 caner candan
//

#ifndef __DATABASE_H__
# define __DATABASE_H__

# include "Singleton.hpp"
# include "SQLiteWrapper.h"

class	Database : public Singleton<Database>
{
  friend class	Singleton<Database>;
public:
  SQLiteWrapper&	operator*();
  SQLiteWrapper&	database();
private:
  Database();
  ~Database();
private:
  SQLiteWrapper	_db;
};

#endif // !__DATABASE_H__

