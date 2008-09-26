//
// SocketClient.h for SocketClient in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Thu Jul 10 21:57:02 2008 caner candan
// Last update Tue Sep  9 17:12:02 2008 caner candan
//

#ifndef __SOCKETCLIENT_H__
# define __SOCKETCLIENT_H__

# include <string>
# include "Socket.h"

class	SocketClient : public Socket
{
public:
  SocketClient();
  SocketClient(int socketServer);

  void		acceptClient(int socketServer);
  std::string	head(void);
};

#endif // !__SOCKETCLIENT_H__
