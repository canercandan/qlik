//
// main.cpp for server in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Wed Jul  9 21:26:20 2008 caner candan
// Last update Thu Jul 31 19:57:45 2008 caner candan
//

#include <sqlite3.h>
#include <cstdlib>
#include <iostream>
#include "SQLiteWrapper.h"
#include "SocketServer.h"
#include "SocketClient.h"
#include "Server.h"

int		main(int ac, char **av)
{
  Server	s(true);

  s.addServer(ac == 2 ? ::atoi(av[1]) : 4243);
  s.loopServer();
  return (0);
}
