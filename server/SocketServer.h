//
// SocketServer.h for SocketServer in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Wed Jul  9 21:27:02 2008 caner candan
// Last update Thu Jul 10 14:06:03 2008 caner candan
//

#ifndef __SOCKETSERVER_H__
# define __SOCKETSERVER_H__

# include <string>
# include "Socket.h"

# define MAX_LISTEN	42

class	SocketServer : public Socket
{
public:
  SocketServer(bool verbose = false);
  SocketServer(int port, bool verbose = false);
  SocketServer(const SocketServer&);
  ~SocketServer();
  SocketServer	&operator=(const SocketServer&);

  void	SocketServer::createSocket(int port = 12345);
  std::string	head(void);
};

#endif // !__SOCKETSERVER_H__
