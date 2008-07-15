//
// main.cpp for server in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Wed Jul  9 21:26:20 2008 caner candan
// Last update Tue Jul 15 00:40:48 2008 caner candan
//

#include <cstdlib>
#include <iostream>
#include "SocketServer.h"
#include "SocketClient.h"
#include "Server.h"

int		main(int ac, char **av)
{
  Server	s(true);

  s.addServer(ac == 2 ? ::atoi(av[1]) : 12345);
  s.loopServer();
  return (0);
}
