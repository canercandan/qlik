//
// SocketServer.cpp for SocketServer in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Wed Jul  9 21:29:14 2008 caner candan
// Last update Mon Sep 29 14:49:04 2008 caner candan
//

#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <sstream>
#include "SocketClient.h"
#include "State.h"
#include "Config.h"

SocketClient::SocketClient()
{}

SocketClient::SocketClient(int socketServer)
{
  acceptClient(socketServer);
}

void	SocketClient::acceptClient(int socketServer)
{
  Config*	config = Config::getInstance();

  try
    {
      if ((this->_socket = accept(socketServer, NULL, NULL)) < 0)
	throw true;
    }
  catch (bool)
    {
      if (config->isVerbose())
	std::cout << this->head()
		  << "accept error"
		  << std::endl;
      State::getInstance()->setState(State::ERROR);
      this->closeSocket();
    }
}

std::string	SocketClient::head(void)
{
  std::stringstream	ss;

  ss << "SocketClient: [" << this->_socket << "] ";
  return (ss.str());
}
