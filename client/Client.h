//
// Client.h for Client in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Jul 15 15:24:41 2008 caner candan
// Last update Tue Sep  2 00:58:57 2008 caner candan
//

#ifndef __CLIENT_H__
# define __CLIENT_H__

# include <QMainWindow>
# include <QtNetwork>
# include "ui_Client.h"
# include "Message.h"
# include "Contact.h"

# define WELCOME		"welcome"
# define LOGIN			"login"
# define LOGOUT			"logout"
# define CREATE			"create"
# define CREDIT			"credit"
# define STATUS			"status"
# define CLIENTS		"clients"
# define ACCOUNTS		"accounts"
# define MESSAGE		"message"
# define SERVICES_WEB		"services_web"
# define SERVICES_STREAM	"services_stream"
# define SERVICES_WEB_DETAIL	"services_web_detail"
# define SERVICES_STREAM_DETAIL	"services_stream_detail"
# define OFFER_WEB		"offer_web"
# define OFFER_STREAM		"offer_stream"
# define CREATE_OFFER_WEB	"create_offer_web"
# define CREATE_OFFER_STREAM	"create_offer_stream"
# define CREATE_WEB		"create_web"
# define CREATE_STREAM		"create_stream"
# define NEWS			"news"
# define NEWS_DETAIL		"news_detail"

# define RATIO_WEB_SPACE	100
# define RATIO_WEB_DB		1

# define RATIO_STREAM_SLOT	5
# define RATIO_STREAM_BITS	24

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

  enum	ServiceType
    {
      WEB,
      STREAM
    };

  static Actions	actions[];

  static void	actWelcome(Client*, const QStringList&);
  static void	actLogin(Client*, const QStringList&);
  static void	actLogout(Client*, const QStringList&);
  static void	actCreate(Client*, const QStringList&);
  static void	actCredit(Client*, const QStringList&);
  static void	actStatus(Client*, const QStringList&);
  static void	actClients(Client*, const QStringList&);
  static void	actAccounts(Client*, const QStringList&);
  static void	actMessage(Client*, const QStringList&);
  static void	actServicesWeb(Client*, const QStringList&);
  static void	actServicesStream(Client*, const QStringList&);
  static void	actServicesWebDetail(Client*, const QStringList&);
  static void	actServicesStreamDetail(Client*, const QStringList&);
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
  MessageMap	_mm;
  QString	_userCreated;
  int		_credit;
};

#endif // !__CLIENT_H__
