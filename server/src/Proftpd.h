//
// Proftpd.h for server in /home/candan_c/cu/rendu/qlik/server/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Thu Oct 23 19:37:52 2008 caner candan
// Last update Thu Oct 23 19:39:34 2008 caner candan
//

#ifndef __PROFTPD_H__
# define __PROFTPD_H__

# include "IServerFtp.h"
# include "Client.h"

class	Proftpd : public IServerFtp
{
public:
  Proftpd(Client*);

  void	createJail(const std::string& user,
		   const std::string& passwd,
		   const std::string& dir,
		   const int& quota) = 0;
};

#endif // !__PROFTPD_H__
