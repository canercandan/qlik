//
// Client.h for Client in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Jul 15 15:24:41 2008 caner candan
// Last update Sat Jul 19 14:43:42 2008 caner candan
//

#ifndef __CLIENT_H__
# define __CLIENT_H__

# include <QMainWindow>
# include <QtNetwork>
# include "ui_Client.h"
# include "Socket.h"

class	Client : public QMainWindow, public Ui::Client
{
  Q_OBJECT

  public:
  Client(QWidget *parent = NULL);
  ~Client();
private slots:
  void	on_actionSignUp_triggered();
  void	on_actionSignIn_triggered();
  void	on_actionSignOut_triggered();
  void	on_actionQuit_triggered();
private:
  Socket	*_socket;
};

#endif // !__CLIENT_H__
