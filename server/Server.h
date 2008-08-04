//
// Server.h for Server in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Fri Jul 11 20:34:03 2008 caner candan
// Last update Sun Aug  3 13:52:44 2008 caner candan
//

#ifndef __SERVER_H__
# define __SERVER_H__

# include <list>
# include <string>
# include "Client.h"
# include "SQLiteWrapper.h"

# define MESG_OK	"OK\n"
# define MESG_KO	"KO\n"
# define MESG_EMPTY	""
# define MESG_BEGIN	"BEGIN\n"
# define MESG_END	"END\n"

# define WELCOME		"welcome\n"
# define LOGIN			"login"
# define LOGOUT			"logout"
# define CREATE			"create"
# define STATUS			"status"
# define CLIENTS		"clients"
# define ACCOUNTS		"accounts"
# define MESSAGE		"message"
# define SERVICES_WEB		"services_web"
# define SERVICES_STREAM	"services_stream"
# define OFFER_WEB		"offer_web"
# define OFFER_STREAM		"offer_stream"
# define CREATE_WEB		"create_web"
# define CREATE_STREAM		"create_stream"
# define NEWS			"news"
# define NEWS_DETAIL		"news_detail"

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

  static Actions	actions[];

  static void	actLogin(Server*, Client*);
  static void	actLogout(Server*, Client*);
  static void	actCreate(Server*, Client*);
  static void	actStatus(Server*, Client*);
  static void	actClients(Server*, Client*);
  static void	actAccounts(Server*, Client*);
  static void	actMessage(Server*, Client*);
  static void	actServicesWeb(Server*, Client*);
  static void	actServicesStream(Server*, Client*);
  static void	actOfferWeb(Server*, Client*);
  static void	actOfferStream(Server*, Client*);
  static void	actCreateWeb(Server*, Client*);
  static void	actCreateStream(Server*, Client*);
  static void	actNews(Server*, Client*);
  static void	actNewsDetail(Server*, Client*);
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

  bool	existLogin(const std::string& login);
  bool	existLoginPasswd(const std::string& login,
			 const std::string& passwd);
  bool	alreadyConnected(const std::string& login);

  Client	*findClient(const std::string& login);

  bool	notConnected(Client*);

  std::string	head(void);
private:
  SQLiteWrapper		_sql;
  listClients		_clients;
  bool			_verbose;
};

#endif // !__SERVER_H__
