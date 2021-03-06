// Client.h --- 
// 
// Filename: Client.h
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 00:43:46 2008 (+0200)
// Version: 
// Last-Updated: Tue Dec  9 12:03:55 2008 (+0200)
//           By: Caner Candan
//     Update #: 19
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

#ifndef __CLIENT_H__
# define __CLIENT_H__

# include <QMainWindow>
# include <QtNetwork>
# include <string>
# include "ui_Client.h"
# include "Message.h"
# include "Contact.h"

class	Client : public QMainWindow, public Ui::Client
{
  Q_OBJECT

  typedef QMap<QString, Message*>	MessageMap;
public:
  enum	ServiceType {TYPE_WEB, TYPE_STREAM};
public:
  Client(QWidget *parent = NULL);
  ~Client();

  void	openMessage(const QString& sName);
  void	destroyMessages();
  void	appendMessage(const QString& sName,
		      const QString& from,
		      const QString& body);

  void	loadNews();
  void	loadClients();
  void	loadMyContact(const QString& contact,
		      const int& right);
  void	loadAllContact(const QString& contact,
		       const int& right);

  void	createOfferWeb();
  void	createOfferStream();
  void	createWeb();
  void	createStream();

  void	login();
  void	logout();

  void	addHistory(const ServiceType& type,
		   const QString& desribe,
		   const int& price);
  void	addToContactsList(const Contact&);

  int	getCredit() const;
  void	setCredit(const int&);

  void	showServiceSelected();
private slots:
  void	on_actionSignUp_triggered();
  void	on_actionSignIn_triggered();
  void	on_actionSignOut_triggered();

  void	on_serviceAdd_clicked();
  void	on_serviceManage_clicked();

  void	on_newsRead_clicked();
  void	on_newsAdd_clicked();
  void	on_newsDelete_clicked();

  void	on_talkOpen_clicked();
  void	on_talkMyContactsAdd_clicked();
  void	on_talkMyContactsDel_clicked();
  void	on_talkAllContactsAdd_clicked();

  void	on_adminModify_clicked();

  void	on_adminCreditAccept_clicked();
  void	on_adminCreditReject_clicked();

  void	on_serverHalt_clicked();
  void	on_serverReload_clicked();
  void	on_serverPlay_clicked();
  void	on_serverBreak_clicked();

  void	_connectedToServer();
  void	_readAction();
  void	_sendAction();
  void	_displayError(QAbstractSocket::SocketError);

  void	loadOffers(int);
  void	_loadPages(int);
  void	_loadServices(int);
  void	_loadHistory(int);
  void	_loadAdmin(int);

  void	_beforeClose(QObject*);
private:
  void		_loadOptions();

  QVariant	_getKeyValue(const QString& key);
  bool		_keyExist(const QString&);
  void		_saveKey(const QString& key, const QVariant& value);

  bool	_acceptRejectCredit();

private:
  MessageMap	_mm;
  QString	_userCreated;

public:
  const int&	getRight(void){return (_right);}
  void	setRight(const int& right){_right = right;}
private:
  int	_right;
};

#endif // !__CLIENT_H__

// 
// Client.h ends here
