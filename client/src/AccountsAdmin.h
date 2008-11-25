//
// AccountsAdmin.h for client in /home/candan_c/cu/rendu/qlik/client/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Mon Nov 24 00:55:20 2008 caner candan
// Last update Tue Nov 25 13:43:38 2008 caner candan
//

#ifndef __ACCOUNTSADMIN_H__
# define __ACCOUNTSADMIN_H__

# include <QDialog>
# include "Singleton.hpp"
# include "ui_AccountsAdmin.h"

class	AccountsAdmin : public QDialog, public Singleton<AccountsAdmin>,
			public Ui::AccountsAdmin
{
  Q_OBJECT

  friend class	Singleton<AccountsAdmin>;
private slots:
  void	on_minus_clicked();
  void	on_plus_clicked();

  void	on_ok_clicked();
  void	on_cancel_clicked();
private:
  AccountsAdmin(QWidget* parent = NULL);
};

#endif // !__ACCOUNTSADMIN_H__
