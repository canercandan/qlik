//
// Action.h for server in /home/candan_c/cu/rendu/qlik/server/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Oct 26 17:42:54 2008 caner candan
// Last update Mon Nov 24 12:37:52 2008 caner candan
//

#ifndef __ACTION_H__
# define __ACTION_H__

# include <sys/types.h>
# include <unistd.h>
# include <map>
# include <string>
# include <sstream>
# include "Server.h"
# include "Client.h"

class	Action
{
public:
  typedef void	(Action::*callback)();

  typedef std::pair<bool, int>			pairParam;
  typedef std::pair<callback, pairParam>	pairCallback;
  typedef std::map<std::string, pairCallback>	mapAction;
public:
  Action(Server*, Client*);
  ~Action();

  void	execute();
private:
  void	_fillMapAction();

  void	_actLogin();
  void	_actLogout();
  void	_actCreate();

  void	_actCredit();
  void	_actStatus();
  void	_actRight();

  void	_actClients();

  void	_actAccounts();
  void	_actAccountsModify();

  void	_actMessage();

  void	_actWeb();
  void	_actStream();

  void	_actWebDetail();
  void	_actStreamDetail();

  void	_actOfferWeb();
  void	_actOfferStream();

  void	_actCreateOfferWeb();
  void	_actCreateOfferStream();

  void	_actCreateWeb();
  void	_actCreateStream();

  void	_actNews();
  void	_actNewsDetail();
  void	_actNewsAdd();
  void	_actNewsDelete();

  void	_actWebStatus();
  void	_actWebStart();
  void	_actWebStop();

  void	_actStreamStatus();
  void	_actStreamStart();
  void	_actStreamStop();

  void	_actHalt();
  void	_actBreak();
  void	_actPlay();
  void	_actReload();

  bool	_existLogin(const std::string& login);
  bool	_existLoginPasswd(const std::string& login,
			  const std::string& passwd);
  bool	_alreadyConnected(const std::string& login);

  std::string	_generatePasswd();

  bool	_streamOnline(const std::string& name);
  void	_sendServices(const std::string& req);
  void	_sendOffer(const std::string& req);
private:
  Server*	_server;
  Client*	_client;

  mapAction	_mapAction;

  std::stringstream	_buffer;
};

#endif // !__ACTION_H__
