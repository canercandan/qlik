//
// IServerFtp.h for server in /home/candan_c/cu/rendu/qlik/server/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Thu Oct 23 19:31:36 2008 caner candan
// Last update Thu Oct 23 19:35:08 2008 caner candan
//

#ifndef __ISERVERFTP_H__
# define __ISERVERFTP_H__

# include <string>

class	IServerFtp
{
public:
  virtual ~IServerFtp(){}

  virtual void	createJail(const std::string& user,
			   const std::string& passwd,
			   const std::string& dir,
			   const int& quota) = 0;
};

#endif // !__ISERVERFTP_H__
