//
// Select.h for server in /home/candan_c/cu/rendu/qlik/server/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Oct 26 17:06:21 2008 caner candan
// Last update Thu Nov 13 19:55:54 2008 caner candan
//

#ifndef __SELECT_H__
# define __SELECT_H__

# include <string>
# include "Client.h"
# include "Server.h"
# include "ISignalManager.h"

class	Select : public ISignalManager
{
public:
  Select(Server*);
  ~Select();

  void	start();

  void	signal();
private:
  void	_addServer(int port);
  void	_addClient(Client* server);

  void	_setFd(fd_set& fdRead, fd_set& fdWrite, int& fdMax);
  void	_issetFd(fd_set& fdRead, fd_set& fdWrite);

  void	_serverRead(Client* server);

  void	_clientRead(Client* client);
  void	_clientWrite(Client* client);
private:
  Server*	_server;
};

#endif // !__SELECT_H__
