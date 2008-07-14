//
// SocketClient.h for SocketClient in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Thu Jul 10 21:57:02 2008 caner candan
// Last update Thu Jul 10 22:00:52 2008 caner candan
//

#ifndef __SOCKETCLIENT_H__
# define __SOCKETCLIENT_H__

# include <string>
# include "Socket.h"

class	SocketClient : public Socket
{
public:
  SocketClient(bool verbose = false);
  SocketClient(int socketServer, bool verbose = false);
  SocketClient(const SocketClient&);
  ~SocketClient();
  SocketClient	&operator=(const SocketClient&);

  void	SocketClient::acceptClient(int socketServer);
  std::string	head(void);
};

#endif // !__SOCKETCLIENT_H__
