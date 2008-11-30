// Action.h --- 
// 
// Filename: Action.h
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 01:44:10 2008 (+0200)
// Version: 
// Last-Updated: Sun Nov 30 04:15:53 2008 (+0200)
//           By: Caner Candan
//     Update #: 27
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

# include <sys/types.h>
# include <unistd.h>
# include <map>
# include <string>
# include <sstream>
# include "Server.h"
# include "Client.h"
# include "Service.h"
# include "Stream.h"
# include "Web.h"

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
  void	_createStream(Stream&);
  void	_createWeb(Web&);
  void	_renewExpiredDate(Service&);
  void	_acceptCredit(int idUser, int credit);
  void	_rejectCredit(int id);
private:
  Server*	_server;
  Client*	_client;

  mapAction	_mapAction;

  std::stringstream	_buffer;
};

#endif // !__ACTION_H__

// 
// Action.h ends here
