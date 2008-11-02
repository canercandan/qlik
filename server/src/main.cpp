//
// main.cpp for server in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Wed Jul  9 21:26:20 2008 caner candan
// Last update Sun Oct 26 19:22:39 2008 caner candan
//

#include <iostream>
#include "Server.h"
#include "Config.h"

int		main(void)
{
  Config*	config = Config::getInstance();

  if (config->isDaemon())
    {
      pid_t		pid;

      if ((pid = fork()))
	{
	  std::cout << "Server started..." << std::endl
		    << "Detached to pid [" << pid << "]." << std::endl;
	  return (0);
	}
    }

  Server	s;

  s.start();

  return (0);
}
