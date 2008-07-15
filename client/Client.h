//
// Client.h for Client in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Jul 15 15:24:41 2008 caner candan
// Last update Tue Jul 15 15:57:42 2008 caner candan
//

#ifndef __CLIENT_H__
# define __CLIENT_H__

# include <QMainWindow>
# include "ui_Client.h"

class	Client : public QMainWindow, private Ui::Client
{
  Q_OBJECT

  public:
  Client(QWidget *parent = NULL);
  ~Client();
private slots:
  void	on_actionSignIn_triggered();
  void	on_actionSignOut_triggered();
  void	on_actionQuit_triggered();
private:
};

#endif // !__CLIENT_H__
