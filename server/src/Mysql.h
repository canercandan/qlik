//
// Mysql.h for server in /home/candan_c/cu/rendu/qlik/server/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Thu Oct 23 20:07:41 2008 caner candan
// Last update Thu Oct 23 20:09:16 2008 caner candan
//

#ifndef __MYSQL_H__
# define __MYSQL_H__

# include "IServerSql.h"
# include "Client.h"

class	Mysql
{
public:
  Mysql(Client*);

  void	createDb(const std::string& user,
		 const std::string& passwd,
		 const std::string& name);
};

#endif // !__MYSQL_H__
