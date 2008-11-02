//
// Client.h for Client in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Jul 15 15:24:41 2008 caner candan
// Last update Thu Oct 30 16:17:41 2008 caner candan
//

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

  void	loadClients();
  void	loadMyContact(const QString& contact);
  void	loadAllContact(const QString& contact);

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

  const int&	getCredit() const;
  void	setCredit(const int&);
  void	addCredit(const int&);
  void	subCredit(const int&);

  void	refreshList();
private slots:
  void	on_actionSignUp_triggered();
  void	on_actionSignIn_triggered();
  void	on_actionSignOut_triggered();

  void	on_actionRefresh_triggered();

  void	on_actionQuit_triggered();
  void	on_actionAbout_triggered();
  void	on_actionOptions_triggered();
  void	on_actionAccounts_triggered();

  void	on_serviceAdd_clicked();
  void	on_serviceManage_clicked();
  void	on_serviceCredit_clicked();

  void	on_newsRead_clicked();

  void	on_talkOpen_clicked();
  void	on_talkMyContactsAdd_clicked();
  void	on_talkMyContactsDel_clicked();
  void	on_talkAllContactsAdd_clicked();

  void	connectedToServer();
  void	readAction();
  void	sendAction();
  void	displayError(QAbstractSocket::SocketError);

  void	loadOffers(int);
  void	loadPages(int);
  void	loadServices(int);
  void	loadHistory(int);
private:
  QVariant	_getKeyValue(const QString& key);
  bool		_keyExist(const QString&);
  void		_saveKey(const QString& key, const QVariant& value);
private:
  MessageMap	_mm;
  QString	_userCreated;
  int		_credit;
};

#endif // !__CLIENT_H__
