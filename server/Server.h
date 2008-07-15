//
// Server.h for Server in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Fri Jul 11 20:34:03 2008 caner candan
// Last update Tue Jul 15 13:27:57 2008 caner candan
//

#ifndef __SERVER_H__
# define __SERVER_H__

# include <list>
# include <string>
# include "Client.h"

# define NB_ACTIONS	9

# define MESG_OK	"OK\n"
# define MESG_KO	"KO\n"
# define MESG_EMPTY	""
# define MESG_BEGIN	"BEGIN\n"
# define MESG_END	"END\n"
# define MESG_WELCOME	"WELCOME\n"

# define ACCOUNT_FILE	"account.cfg"

class	Server
{
public:
  typedef std::list<Client*>	listClients;
  typedef void	(*fct)(Server*, Client*);

  struct	Actions
  {
    std::string	keyword;
    fct		func;
    std::string	retMesg;
  };

  static Actions	actions[NB_ACTIONS];

  static bool	existLogin(const std::string& login);
  static bool	existLoginPasswd(const std::string& login,
				 const std::string& passwd,
				 int& creditFile);
  static bool	alreadyConnected(const std::string& login,
				 Server*);
  static Client	*findClient(const std::string& login,
			    Server*);
  static bool	notConnected(Client*);

  static void	actLogin(Server*, Client*);
  static void	actLogout(Server*, Client*);
  static void	actCreate(Server*, Client*);
  static void	actStatus(Server*, Client*);
  static void	actClients(Server*, Client*);
  static void	actAccounts(Server*, Client*);
  static void	actMessage(Server*, Client*);
  static void	actServices(Server*, Client*);
  static void	actCreateService(Server*, Client*);
public:
  Server(bool verbose = false);
  Server(const Server&);
  ~Server();
  Server&	operator=(const Server&);

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

  std::string	head(void);
private:
  listClients	_clients;
  bool		_verbose;
};

#endif // !__SERVER_H__
