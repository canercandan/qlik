//
// Client.h for Client in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Jul 15 15:24:41 2008 caner candan
// Last update Sun Aug  3 19:03:07 2008 caner candan
//

#ifndef __CLIENT_H__
# define __CLIENT_H__

# include <QMainWindow>
# include <QtNetwork>
# include "ui_Client.h"
# include "Service.h"

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
# define CREATE_SERVICE		"create_service"
# define NEWS			"news"
# define NEWS_DETAIL		"news_detail"

class	Client : public QMainWindow, public Ui::Client
{
  Q_OBJECT

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
  static void	actCreateService(Client*, const QStringList&);
  static void	actNews(Client*, const QStringList&);
  static void	actNewsDetail(Client*, const QStringList&);
public:
  Client(QWidget *parent = NULL);
  ~Client();

  void	closeSocket();
  void	login();
  void	logout();
private slots:
  void	on_actionSignUp_triggered();
  void	on_actionSignIn_triggered();
  void	on_actionSignOut_triggered();
  void	on_actionQuit_triggered();
  void	on_actionInformation_triggered();
  void	on_actionHelp_triggered();

  void	on_addService_clicked();

  void	on_refreshNews_clicked();
  void	on_readNews_clicked();

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
  QString	_username;
  QString	_password;
};

#endif // !__CLIENT_H__
