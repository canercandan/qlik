//
// Accounts.h for Accounts in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Mon Aug 11 16:06:11 2008 caner candan
// Last update Tue Aug 19 04:04:56 2008 caner candan
//

#ifndef __ACCOUNTS_H__
# define __ACCOUNTS_H__

# include <QDialog>
# include "Singleton.hpp"
# include "ui_Accounts.h"

class	Accounts : public QDialog, public Singleton<Accounts>,
		   public Ui::Accounts
{
  Q_OBJECT

  friend class	Singleton<Accounts>;
public:
  void	reset();
private slots:
  void	on_save_clicked();
  void	on_done_clicked();
  void	on_manage_clicked();
  void	on_add_clicked();
  void	on_del_clicked();

  void	_modifyPassword(int);
private:
  Accounts(QWidget* parent = NULL);

  void	_loadList();
  void	_loadAccount();
  void	_resetAccount();
};

#endif // !__ACCOUNTS_H__
