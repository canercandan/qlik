//
// Action.h for client in /home/candan_c/cu/rendu/qlik/client/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Thu Oct 30 14:59:43 2008 caner candan
// Last update Mon Nov 24 22:28:32 2008 caner candan
//

#ifndef __ACTION_H__
# define __ACTION_H__

# include <QObject>
# include "Client.h"

class	Action : public QObject
{
public:
  typedef void	(Action::*callback)();

  typedef QPair<callback, int>		pairCallback;
  typedef QMap<QString, pairCallback>	mapAction;
public:
  Action(Client*, const QString& userCreated);

  void	execute();
private:
  void	_fillMapAction();

  void	_actWelcome();

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

  void	_actStreamStatus();
  void	_actStreamStart();
  void	_actStreamStop();

  void	_actHalt();
  void	_actReload();
  void	_actPlay();
  void	_actBreak();
private:
  mapAction	_mapAction;
  Client*	_client;
  QString	_userCreated;
  QStringList	_resList;
};

#endif // !__ACTION_H__
