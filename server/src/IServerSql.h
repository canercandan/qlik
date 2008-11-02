//
// IServerSql.h for server in /home/candan_c/cu/rendu/qlik/server/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Thu Oct 23 20:05:43 2008 caner candan
// Last update Sat Oct 25 12:47:25 2008 caner candan
//

#ifndef __ISERVERSQL_H__
# define __ISERVERSQL_H__

# include <string>

class	IServerSql
{
public:
  virtual ~IServerSql(){}

  virtual void	createDb(const std::string& user,
			 const std::string& passwd,
			 const std::string& name) = 0;
};

#endif // !__ISERVERSQL_H__
