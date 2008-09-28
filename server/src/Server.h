//
// Server.h for Server in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Fri Jul 11 20:34:03 2008 caner candan
// Last update Sun Sep 28 16:58:22 2008 caner candan
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

# define DBFILE	"../db/server.db"

#define PASSWD_CHARACTERS			\
  "abcdefghijklmnopqrstuvwxyz"			\
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"			\
  "0123456789"					\
  "!\"#$%&'()*+,-./:;<=>?[\\]^_`{|}~"

#define PASSWD_SIZE	8

class	Server : public ISignalManager
{
public:
  typedef std::list<Client*>		listClients;
  typedef std::map<std::string, pid_t>	mapPid;

  typedef void	(*fct)(Server*, Client*);

  struct	Actions
  {
    std::string	keyword;
    fct		func;
    std::string	retMesg;
  };

  static Actions	actions[];

  static void	actLogin(Server*, Client*);
  static void	actLogout(Server*, Client*);
  static void	actCreate(Server*, Client*);
  static void	actCredit(Server*, Client*);
  static void	actStatus(Server*, Client*);
  static void	actClients(Server*, Client*);
  static void	actAccounts(Server*, Client*);
  static void	actMessage(Server*, Client*);
  static void	actServicesWeb(Server*, Client*);
  static void	actServicesStream(Server*, Client*);
  static void	actServicesWebDetail(Server*, Client*);
  static void	actServicesStreamDetail(Server*, Client*);
  static void	actOfferWeb(Server*, Client*);
  static void	actOfferStream(Server*, Client*);
  static void	actCreateOfferWeb(Server*, Client*);
  static void	actCreateOfferStream(Server*, Client*);
  static void	actCreateWeb(Server*, Client*);
  static void	actCreateStream(Server*, Client*);
  static void	actNews(Server*, Client*);
  static void	actNewsDetail(Server*, Client*);

  static std::string	generatePasswd();
public:
  Server();
  Server(const Server&);
  ~Server();
  Server&	operator=(const Server&);

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
private:
  SQLiteWrapper	_sql;
  listClients	_clients;
  mapPid	_mapPid;
};

#endif // !__SERVER_H__
