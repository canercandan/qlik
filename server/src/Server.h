//
// Server.h for Server in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Fri Jul 11 20:34:03 2008 caner candan
// Last update Mon Sep 29 01:32:21 2008 caner candan
//

#ifndef __SERVER_H__
# define __SERVER_H__

# include <sys/types.h>
# include <unistd.h>
# include <list>
# include <map>
# include <string>
# include "Client.h"
# include "SQLiteWrapper.h"
# include "ISignalManager.h"

class	Server : public ISignalManager
{
public:
  typedef void	(Server::*callback)(Client*);

  typedef std::pair<callback, std::string>	pairCallback;
  typedef std::map<std::string, pairCallback>	mapAction;

  typedef std::list<Client*>		listClients;
  typedef std::map<std::string, pid_t>	mapPid;
public:
  Server();
  ~Server();

  void	signal();

  void	destroyListClients();
  void	addServer(int port);
  void	addClient(Client *server);

  const listClients&	getListClients(void) const;

  void	setFd(fd_set& fdRead, fd_set& fdWrite, int& fdMax);
  void	issetFd(fd_set& fdRead, fd_set& fdWrite);

  void	loopServer(void);

  void	serverRead(Client *server);
  void	clientRead(Client *client);
  void	clientWrite(Client *client);

  void	executeAction(Client *client);

  bool	existLogin(const std::string& login);
  bool	existLoginPasswd(const std::string& login,
			 const std::string& passwd);
  bool	alreadyConnected(const std::string& login);

  Client	*findClient(const std::string& login);

  bool	notConnected(Client*);

  bool	enoughCredit(const int&, Client*);
  void	addCredit(const int&, Client*);
  void	subCredit(const int&, Client*);

  std::string	head(void);

  void	actLogin(Client*);
  void	actLogout(Client*);
  void	actCreate(Client*);
  void	actCredit(Client*);
  void	actStatus(Client*);
  void	actClients(Client*);
  void	actAccounts(Client*);
  void	actMessage(Client*);
  void	actServicesWeb(Client*);
  void	actServicesStream(Client*);
  void	actServicesWebDetail(Client*);
  void	actServicesStreamDetail(Client*);
  void	actOfferWeb(Client*);
  void	actOfferStream(Client*);
  void	actCreateOfferWeb(Client*);
  void	actCreateOfferStream(Client*);
  void	actCreateWeb(Client*);
  void	actCreateStream(Client*);
  void	actNews(Client*);
  void	actNewsDetail(Client*);

  std::string	generatePasswd();
private:
  SQLiteWrapper	_sql;
  mapAction	_mapAction;
  listClients	_clients;
  mapPid	_mapPid;
};

#endif // !__SERVER_H__
