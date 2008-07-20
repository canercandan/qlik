//
// Client.h for Client in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Jul 15 15:24:41 2008 caner candan
// Last update Sun Jul 20 20:51:58 2008 caner candan
//

#ifndef __CLIENT_H__
# define __CLIENT_H__

# include <QMainWindow>
# include <QtNetwork>
# include "ui_Client.h"

# define HOST	"localhost"
# define PORT	4242

# define NB_ACTIONS	9

class	Client : public QMainWindow, public Ui::Client
{
  Q_OBJECT

  public:
  typedef void	(*fct)(Client*, const QStringList&);

  enum	ActionId
    {
      LOGIN,
      LOGOUT,
      CREATE,
      STATUS,
      CLIENTS,
      ACCOUNTS,
      MESSAGE,
      SERVICES,
      CREATE_SERVICE
    };

  struct	Actions
  {
    fct		func;
  };

  static Actions	actions[NB_ACTIONS];

  static void	actLogin(Client*, const QStringList&);
  static void	actLogout(Client*, const QStringList&);
  static void	actCreate(Client*, const QStringList&);
  static void	actStatus(Client*, const QStringList&);
  static void	actClients(Client*, const QStringList&);
  static void	actAccounts(Client*, const QStringList&);
  static void	actMessage(Client*, const QStringList&);
  static void	actServices(Client*, const QStringList&);
  static void	actCreateService(Client*, const QStringList&);

public:
  Client(QWidget *parent = NULL);
  ~Client();

  void	closeSocket();
private slots:
  void	on_actionSignUp_triggered();
  void	on_actionSignIn_triggered();
  void	on_actionSignOut_triggered();
  void	on_actionQuit_triggered();
  void	on_actionInformation_triggered();

  void	connectedToServer();
  void	readAction();
  void	sendAction();
  void	displayError(QAbstractSocket::SocketError);
private:
  QTcpSocket	*_socket;
  QString	_username;
  QString	_password;
};

#endif // !__CLIENT_H__
