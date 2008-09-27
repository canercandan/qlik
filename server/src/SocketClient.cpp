//
// SocketServer.cpp for SocketServer in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Wed Jul  9 21:29:14 2008 caner candan
// Last update Tue Sep  2 14:13:04 2008 caner candan
//

#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <sstream>
#include "SocketClient.h"
#include "State.h"

SocketClient::SocketClient()
{}

SocketClient::SocketClient(int socketServer)
{
  acceptClient(socketServer);
}

void	SocketClient::acceptClient(int socketServer)
{
  try
    {
      if ((this->_socket = accept(socketServer, NULL, NULL)) < 0)
	throw true;
    }
  catch (bool)
    {
#ifdef DEBUG
      std::cout << this->head()
		<< "accept error"
		<< std::endl;
#endif // !DEBUG
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
