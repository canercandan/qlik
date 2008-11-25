//
// News.h for client in /home/candan_c/cu/rendu/qlik/client/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sat Nov 22 00:59:54 2008 caner candan
// Last update Sat Nov 22 01:56:57 2008 caner candan
//

#ifndef __NEWS_H__
# define __NEWS_H__

# include <QDialog>
# include "Singleton.hpp"
# include "ui_News.h"

class	News : public QDialog, public Singleton<News>,
	       public Ui::News
{
  Q_OBJECT

  friend class	Singleton<News>;
private slots:
  void	on_readClose_clicked();
  void	on_addOk_clicked();
  void	on_addCancel_clicked();
private:
  News(QWidget* parent = NULL);
};

#endif // !__NEWS_H__
