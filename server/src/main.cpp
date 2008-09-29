//
// main.cpp for server in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Wed Jul  9 21:26:20 2008 caner candan
// Last update Mon Sep 29 00:50:05 2008 caner candan
//

#include <cstdlib>
#include <iostream>
#include "Server.h"
#include "XmlConfig.h"

int		main(int ac, char **av)
{
  Server	s;
  XmlConfig*	config = XmlConfig::getInstance();

  if (config->xmlGetParam("/server/daemon", "enabled") == "true")
    {
      pid_t		pid;

      if ((pid = fork()))
	{
	  std::cout << "Server started..." << std::endl
		    << "Detached to pid [" << pid << "]." << std::endl;
	  return (0);
	}
    }
  s.addServer(ac == 2 ? ::atoi(av[1]) : 4243);
  s.loopServer();
  return (0);
}
