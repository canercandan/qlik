//
// main.cpp for server in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Wed Jul  9 21:26:20 2008 caner candan
// Last update Tue Sep  9 17:16:57 2008 caner candan
//

#include <cstdlib>
#include <iostream>
#include "Server.h"

int		main(int ac, char **av)
{
  Server	s;
  pid_t		pid;

#ifndef DEBUG
  if ((pid = fork()))
    {
      std::cout << "Server started..." << std::endl
		<< "Detached to pid [" << pid << "]." << std::endl;
      return (0);
    }
#endif // !DEBUG
  s.addServer(ac == 2 ? ::atoi(av[1]) : 4243);
  s.loopServer();
  return (0);
}
