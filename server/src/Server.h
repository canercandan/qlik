//
// Server.h for Server in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Fri Jul 11 20:34:03 2008 caner candan
// Last update Thu Nov 13 22:22:08 2008 caner candan
//

#ifndef __SERVER_H__
# define __SERVER_H__

# include <sys/types.h>
# include <list>
# include <map>
# include <string>
# include "Client.h"
# include "ISignalManager.h"

class	Server : public ISignalManager
{
public:
  typedef std::list<Client*>	listClients;

  typedef std::map<std::string, pid_t>		mapClientPid;
  typedef std::map<std::string, mapClientPid>	mapStreamPid;
public:
  Server();
  ~Server();

  void	start();

  Client*	findClient(const std::string& login);

  listClients&	getListClients();
  mapStreamPid&	getMapStreamPid();

  void	signal();
private:
  void	_destroyListClients();
private:
  listClients	_clients;
  mapStreamPid	_mapStreamPid;
};

#endif // !__SERVER_H__
