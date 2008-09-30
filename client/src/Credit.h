//
// Credit.h for Credit in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Mon Aug 11 16:06:11 2008 caner candan
// Last update Mon Sep 29 19:57:09 2008 caner candan
//

#ifndef __CREDIT_H__
# define __CREDIT_H__

# include <QDialog>
# include "Singleton.hpp"
# include "ui_Credit.h"

class	Credit : public QDialog, public Singleton<Credit>,
		 public Ui::Credit
{
  Q_OBJECT

  friend class	Singleton<Credit>;
public:
  void	reset();
private slots:
  void	on_buy_clicked();
  void	on_cancel_clicked();
private:
  Credit(QWidget* parent = NULL);
};

#endif // !__CREDIT_H__
