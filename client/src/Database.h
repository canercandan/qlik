//
// Database.h for Database in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Mon Aug 11 16:06:11 2008 caner candan
// Last update Wed Nov 26 02:31:50 2008 caner candan
//

#ifndef __DATABASE_H__
# define __DATABASE_H__

# include <QtSql>
# include "Singleton.hpp"

# define DBFILE	"client.db"

class	Database : public Singleton<Database>
{
  friend class	Singleton<Database>;
public:
  const QSqlDatabase&	database();

  bool	connect();
  void	close();
private:
  Database();
  ~Database();
private:
  QSqlDatabase	_db;
};

#endif // !__DATABASE_H__
