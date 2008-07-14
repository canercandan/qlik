//
// SocketServer.cpp for SocketServer in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Wed Jul  9 21:29:14 2008 caner candan
// Last update Sun Jul 13 06:55:26 2008 caner candan
//

#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <sstream>
#include "Socket.h"
#include "SocketClient.h"

SocketClient::SocketClient(bool verbose /*= false*/)
  : Socket(verbose)
{}

SocketClient::SocketClient(int socketServer,
			   bool verbose /*= false*/)
  : Socket(verbose)
{
  acceptClient(socketServer);
}

SocketClient::SocketClient(const SocketClient& sc)
  : Socket()
{*this = sc;}

SocketClient::~SocketClient()
{}

SocketClient&	SocketClient::operator=(const SocketClient& sc)
{
  if (this != &sc)
    {
      this->_socket = sc._socket;
      this->_verbose = sc._verbose;
    }
  return (*this);
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
      std::cout << this->head()
		<< "accept error"
		<< std::endl;
      this->closeSocket();
    }
}

std::string	SocketClient::head(void)
{
  std::stringstream	ss;

  ss << "SocketClient: [" << this->_socket << "] ";
  return (ss.str());
}
