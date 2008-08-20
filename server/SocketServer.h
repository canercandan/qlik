//
// SocketServer.h for SocketServer in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Wed Jul  9 21:27:02 2008 caner candan
// Last update Sat Aug 16 22:17:29 2008 caner candan
//

#ifndef __SOCKETSERVER_H__
# define __SOCKETSERVER_H__

# include <string>
# include "Socket.h"

# define MAX_LISTEN	42

class	SocketServer : public Socket
{
public:
  SocketServer();
  SocketServer(int port);
  SocketServer(const SocketServer&);
  ~SocketServer();
  SocketServer	&operator=(const SocketServer&);

  void	SocketServer::createSocket(int port = 12345);
  std::string	head(void);
};

#endif // !__SOCKETSERVER_H__
