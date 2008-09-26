//
// Server.h for Server in /home/candan_c/rendu/ekzay/server
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Fri Jul 11 20:34:03 2008 caner candan
// Last update Fri Sep  5 21:57:59 2008 caner candan
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

# define DBFILE	"db/server.db"

# define MESG_OK	"OK\n"
# define MESG_KO	"KO\n"
# define MESG_EMPTY	""
# define MESG_BEGIN	"BEGIN\n"
# define MESG_END	"END\n"

# define WELCOME		"welcome\n"

# define LOGIN			"login"
// login USERNAME PASSWORD
// -> login (CREDIT|KO)

# define LOGOUT			"logout"
// logout
// -> logout OK

# define CREATE			"create"
// create USERNAME
// -> create (PASSWORD|KO)

# define CREDIT			"credit"
// credit
// -> credit CREDIT

# define STATUS			"status"
// status
// -> status (OK|KO)

# define CLIENTS		"clients"
// clients
// -> clients (BEGIN\n*(USERNAME)\nEND|KO)

# define ACCOUNTS		"accounts"
// accounts
// -> accounts (BEGIN\n*(USERNAME)\nEND|KO)

# define MESSAGE		"message"
// message USERNAME MESSAGE
// -> message (OK|KO)
// -> message FROM MESSAGE

# define SERVICES_WEB		"services_web"
// services_web
// -> services_web (BEGIN\n*(NAME)\nEND|KO)

# define SERVICES_STREAM	"services_stream"
// services_stream
// -> services_stream (BEGIN\n*(NAME)\nEND|KO)

# define SERVICES_WEB_DETAIL	"services_web_detail"
// services_web_detail ROW
// -> services_web_detail (NAME SPACE NB_DB DOMAIN
// CREATED EXPIRED|KO)

# define SERVICES_STREAM_DETAIL	"services_stream_detail"
// services_stream_detail ROW
// -> services_stream_detail (NAME SLOTS BITS TITLE
// CREATED EXPIRED|KO)

# define OFFER_WEB		"offer_web"
// offer_web
// -> offer_web (BEGIN\n*(PRICE NAME)\nEND|KO)

# define OFFER_STREAM		"offer_stream"
// offer_stream
// -> offer_stream (BEGIN\n*(PRICE NAME)\nEND|KO)

# define CREATE_OFFER_WEB	"create_offer_web"
// create_offer_web NAME ROW DOMAIN
// -> create_offer_web (OK|KO)

# define CREATE_OFFER_STREAM	"create_offer_stream"
// create_offer_stream NAME ROW TITLE
// -> create_offer_stream (OK|KO)

# define CREATE_WEB		"create_web"
// create_web NAME SPACE NB_DB DOMAIN
// -> create_web (OK|KO)

# define CREATE_STREAM		"create_stream"
// create_stream NAME SLOTS BITS TITLE
// -> create_stream (OK|KO)

# define NEWS			"news"
// news
// -> news (BEGIN\n*(DATE SUBJECT)\nEND|KO)

# define NEWS_DETAIL		"news_detail"
// news_detail ROW
// -> news_detail (BODY|KO)

# define STREAM_START		"stream_start"
// stream_start NAME
// -> stream_start (OK|KO)

# define STREAM_STOP		"stream_stop"
// stream_stop NAME
// -> stream_stop (OK|KO)

# define RATIO_WEB_SPACE	100
# define RATIO_WEB_DB		1

# define RATIO_STREAM_SLOT	5
# define RATIO_STREAM_BITS	24

#define PASSWD_CHARACTERS			\
  "abcdefghijklmnopqrstuvwxyz"			\
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"			\
  "0123456789"					\
  "!\"#$%&'()*+,-./:;<=>?[\\]^_`{|}~"

#define PASSWD_SIZE	8

class	Server
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