//
// Socket.h for Socket.h in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Wed Jul 16 23:15:46 2008 caner candan
// Last update Sun Jul 20 17:20:22 2008 caner candan
//

#ifndef __SOCKET_H__
# define __SOCKET_H__

# include <QObject>
# include <QtNetwork>
# include "Connect.h"
# include "Create.h"

# define NB_ACTIONS	9

class	Socket : public QObject
{
  Q_OBJECT

  public:
  typedef void	(*fct)(Socket*, const QStringList&);

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

  static void	Socket::actLogin(Socket*, const QStringList&);
  static void	Socket::actLogout(Socket*, const QStringList&);
  static void	Socket::actCreate(Socket*, const QStringList&);
  static void	Socket::actStatus(Socket*, const QStringList&);
  static void	Socket::actClients(Socket*, const QStringList&);
  static void	Socket::actAccounts(Socket*, const QStringList&);
  static void	Socket::actMessage(Socket*, const QStringList&);
  static void	Socket::actServices(Socket*, const QStringList&);
  static void	Socket::actCreateService(Socket*, const QStringList&);
public:
  Socket(QWidget *parent = NULL);
  ~Socket();

  void	connectToServer(const Connect& connect);
  void	createToServer(const Create& create);
  void	close(void);

  void	signOut();

  QTcpSocket	*getSocket(void);
private slots:
  void	signIn();
  void	signUp();
  void	executeAction();
  void	displayError(QAbstractSocket::SocketError socketErr);
private:
  QWidget	*_parent;
  QTcpSocket	*_socket;
  QString	_username;
  QString	_password;
};

#endif // !__SOCKET_H__
