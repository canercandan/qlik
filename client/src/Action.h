// Action.h --- 
// 
// Filename: Action.h
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 00:39:24 2008 (+0200)
// Version: 
// Last-Updated: Thu Dec  4 00:26:24 2008 (+0200)
//           By: Caner Candan
//     Update #: 9
// URL: 
// Keywords: 
// Compatibility: 
// 
// 

// Commentary: 
// 
// 
// 
// 

// Change log:
// 29-Nov-2008    Caner Candan  
//    Last-Updated: Thu Nov 27 00:43:11 2008 (+0200) #2 (Caner Candan)
//    add renew action to web and stream services
// 
// 
// 
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 3, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; see the file COPYING.  If not, write to
// the Free Software Foundation, Inc., 51 Franklin Street, Fifth
// Floor, Boston, MA 02110-1301, USA.

// 
// 

// Code:

#ifndef __ACTION_H__
# define __ACTION_H__

# include <QObject>
# include "Client.h"

class	Action : public QObject
{
  Q_OBJECT

public:
  typedef void	(Action::*callback)();

  typedef QPair<callback, int>		pairCallback;
  typedef QMap<QString, pairCallback>	mapAction;
public:
  Action(Client*, const QString& userCreated);

  void	execute();
private:
  void	_fillMapAction();
  void	_initialize(const QString& action);

  void	_actWelcome();

  void	_actLogin();
  void	_actLogout();
  void	_actCreate();

  void	_actCredit();

  void	_actAddCredit();
  void	_actListCredit();
  void	_actAcceptCredit();
  void	_actRejectCredit();

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

  void	_actRenewWeb();
  void	_actRenewStream();

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

// 
// Action.h ends here
