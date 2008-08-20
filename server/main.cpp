//
// main.cpp for server in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Wed Jul  9 21:26:20 2008 caner candan
// Last update Sat Aug 16 23:55:26 2008 caner candan
//

#include <cstdlib>
#include "Server.h"

int		main(int ac, char **av)
{
  Server	s;

#ifndef DEBUG
  if (fork())
    return (0);
#endif // !DEBUG
  s.addServer(ac == 2 ? ::atoi(av[1]) : 4243);
  s.loopServer();
  return (0);
}
