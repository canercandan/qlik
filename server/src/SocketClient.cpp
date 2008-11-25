//
// SocketServer.cpp for SocketServer in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Wed Jul  9 21:29:14 2008 caner candan
// Last update Thu Nov 13 19:31:31 2008 caner candan
//

#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <sstream>
#include "SocketClient.h"
#include "State.h"
#include "Config.h"

SocketClient::SocketClient(int socket)
{
  _acceptClient(socket);
}

void	SocketClient::_acceptClient(int socket)
{
  Config*	config = Config::getInstance();

  try
    {
      if ((this->_socket = accept(socket, NULL, NULL)) < 0)
	throw true;
    }
  catch (bool)
    {
      if (config->isVerbose())
	std::cout << "SocketClient: [" << _socket << "] "
		  << "accept error"
		  << std::endl;

      State::getInstance()->setLoopState(State::LOOP_ERROR);
      this->closeSocket();
    }
}
