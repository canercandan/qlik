//
// SocketServer.cpp for SocketServer in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Wed Jul  9 21:29:14 2008 caner candan
// Last update Thu Oct 30 13:51:35 2008 caner candan
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cerrno>
#include <string>
#include <iostream>
#include <sstream>
#include "SocketServer.h"
#include "State.h"
#include "Config.h"

SocketServer::SocketServer()
{}

SocketServer::SocketServer(int port)
{
  createSocket(port);
}

void	SocketServer::createSocket(int port /*= 12345*/)
{
  Config*	config = Config::getInstance();

  try
    {
      struct sockaddr_in	addr;
      struct protoent		*pe;

      pe = ::getprotobyname("tcp");
      if ((this->_socket = ::socket(PF_INET, SOCK_STREAM,
				    pe->p_proto)) < 0)
	throw 1;
      addr.sin_family = AF_INET;
      addr.sin_port = ::htons(port);
      addr.sin_addr.s_addr = INADDR_ANY;
      if (bind(this->_socket, (struct sockaddr*)&addr,
	       (socklen_t)sizeof(addr)) < 0)
	throw 2;
      if (listen(this->_socket, MAX_LISTEN) < 0)
	throw 3;
      if (config->isVerbose())
	std::cout << this->head()
		  << "Socket created in "
		  << "localhost : " << port
		  << std::endl;
    }
  catch (int e)
    {
      if (config->isVerbose())
	{
	  std::cout << this->head();
	  if (e == 1)
	    std::cout << "socket error";
	  else if (e == 2)
	    std::cout << "bind error";
	  else if (e == 3)
	    std::cout << "listen error";
	  std::cout << std::endl;
	}

      State::getInstance()->setLoopState(State::LOOP_ERROR);
      this->closeSocket();
    }
}

std::string	SocketServer::head(void)
{
  std::stringstream	ss;

  ss << "SocketServer: [" << this->_socket << "] ";
  return (ss.str());
}
