//
// Proftpd.cpp for server in /home/candan_c/cu/rendu/qlik/server/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Thu Oct 23 19:47:35 2008 caner candan
// Last update Sat Oct 25 12:47:43 2008 caner candan
//

#include "Proftpd.h"

Proftpd::Proftpd(Client* client)
{
  (void)client;
}

void	Proftpd::createJail(const std::string& user,
			    const std::string& passwd,
			    const std::string& dir,
			    const int& quota)
{
  (void)user;
  (void)passwd;
  (void)dir;
  (void)quota;
}
