//
// Client.h for Client in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Jul 15 15:24:41 2008 caner candan
// Last update Fri Aug  8 13:06:02 2008 caner candan
//

#ifndef __CLIENT_H__
# define __CLIENT_H__

# include <QMainWindow>
# include <QtNetwork>
# include "ui_Client.h"
# include "Service.h"
# include "Message.h"

# define HOST	"localhost"
# define PORT	4243

# define WELCOME		"welcome"
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
# define CREATE_OFFER_WEB	"create_offer_web"
# define CREATE_OFFER_STREAM	"create_offer_stream"
# define CREATE_WEB		"create_web"
# define CREATE_STREAM		"create_stream"
# define NEWS			"news"
# define NEWS_DETAIL		"news_detail"

class	Client : public QMainWindow, public Ui::Client
{
  Q_OBJECT

  typedef QMap<QString, Message*>	MessageMap;

public:
  typedef void	(*fct)(Client*, const QStringList&);

  struct	Actions
  {
    QString	keyword;
    fct		func;
  };

  static Actions	actions[];

  static void	actWelcome(Client*, const QStringList&);
  static void	actLogin(Client*, const QStringList&);
  static void	actLogout(Client*, const QStringList&);
  static void	actCreate(Client*, const QStringList&);
  static void	actStatus(Client*, const QStringList&);
  static void	actClients(Client*, const QStringList&);
  static void	actAccounts(Client*, const QStringList&);
  static void	actMessage(Client*, const QStringList&);
  static void	actServicesWeb(Client*, const QStringList&);
  static void	actServicesStream(Client*, const QStringList&);
  static void	actOfferWeb(Client*, const QStringList&);
  static void	actOfferStream(Client*, const QStringList&);
  static void	actCreateOfferWeb(Client*, const QStringList&);
  static void	actCreateOfferStream(Client*, const QStringList&);
  static void	actCreateWeb(Client*, const QStringList&);
  static void	actCreateStream(Client*, const QStringList&);
  static void	actNews(Client*, const QStringList&);
  static void	actNewsDetail(Client*, const QStringList&);
public:
  Client(QWidget *parent = NULL);
  ~Client();

  void	openMessage(const QString& sName);
  void	destroyMessages();
  void	sendMessage(Message*);
  void	appendMessage(const QString& sName,
		      const QString& from,
		      const QString& body);

  void	loadClients();

  void	createOfferWeb();
  void	createOfferStream();
  void	createWeb();
  void	createStream();

  void	closeSocket();
  void	login();
  void	logout();
private slots:
  void	on_actionSignUp_triggered();
  void	on_actionSignIn_triggered();
  void	on_actionSignOut_triggered();
  void	on_actionRefresh_triggered();
  void	on_actionQuit_triggered();
  void	on_actionInformation_triggered();
  void	on_actionHelp_triggered();

  void	on_serviceAdd_clicked();
  void	on_serviceManage_clicked();
  void	on_serviceCredit_clicked();

  void	on_newsRead_clicked();
  void	on_talkOpen_clicked();

  void	connectedToServer();
  void	readAction();
  void	sendAction();
  void	displayError(QAbstractSocket::SocketError);

  void	loadOffers(int);
  void	loadPages(int);
  void	loadServices(int);
private:
  QTcpSocket	*_socket;
  Service	*_service;
  MessageMap	_mm;
};

#endif // !__CLIENT_H__
