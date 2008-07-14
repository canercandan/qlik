//
// main.cpp for server in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Wed Jul  9 21:26:20 2008 caner candan
// Last update Sun Jul 13 04:16:27 2008 caner candan
//

#include <iostream>
#include "SocketServer.h"
#include "SocketClient.h"
#include "Server.h"

int	main(int, char **)
{
  Server	s(true);

  s.addServer(12345);
  s.loopServer();
  return (0);
}
