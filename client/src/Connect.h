//
// Connect.h for Connect in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Jul 15 18:36:03 2008 caner candan
// Last update Sat Nov 22 01:00:27 2008 caner candan
//

#ifndef __CONNECT_H__
# define __CONNECT_H__

# include <QDialog>
# include "ui_Connect.h"

class	Connect : public QDialog, public Ui::Connect
{
  Q_OBJECT

  public:
  Connect(QWidget* parent = NULL);
private slots:
  void	on_ok_clicked();
  void	on_cancel_clicked();
private:
  void	_loadAccounts();
};

#endif // !__CONNECT_H__
