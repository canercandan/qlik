//
// Client.h for Client in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Jul 15 15:24:41 2008 caner candan
// Last update Tue Sep 30 00:15:12 2008 caner candan
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
  typedef void	(Client::*callback)(const QStringList&);

  typedef QMap<QString, callback>	MapAction;

  enum	ServiceType {WEB, STREAM};
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

  void	actWelcome(const QStringList&);
  void	actLogin(const QStringList&);
  void	actLogout(const QStringList&);
  void	actCreate(const QStringList&);
  void	actCredit(const QStringList&);
  void	actStatus(const QStringList&);
  void	actClients(const QStringList&);
  void	actAccounts(const QStringList&);
  void	actMessage(const QStringList&);
  void	actServicesWeb(const QStringList&);
  void	actServicesStream(const QStringList&);
  void	actServicesWebDetail(const QStringList&);
  void	actServicesStreamDetail(const QStringList&);
  void	actOfferWeb(const QStringList&);
  void	actOfferStream(const QStringList&);
  void	actCreateOfferWeb(const QStringList&);
  void	actCreateOfferStream(const QStringList&);
  void	actCreateWeb(const QStringList&);
  void	actCreateStream(const QStringList&);
  void	actNews(const QStringList&);
  void	actNewsDetail(const QStringList&);
private slots:
  void	on_actionSignUp_triggered();
  void	on_actionSignIn_triggered();
  void	on_actionSignOut_triggered();
  void	on_actionRefresh_triggered();
  void	on_actionQuit_triggered();
  void	on_actionInformation_triggered();
  void	on_actionHelp_triggered();
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
  MapAction	_mapAction;
  MessageMap	_mm;
  QString	_userCreated;
  int		_credit;
};

#endif // !__CLIENT_H__
