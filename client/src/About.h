//
// About.h for client in /home/candan_c/cu/rendu/ekzay/client/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Oct 14 19:08:25 2008 caner candan
// Last update Tue Oct 14 23:33:56 2008 caner candan
//

#ifndef __ABOUT_H__
# define __ABOUT_H__

# include <QDialog>
# include "ui_About.h"

class	About : public QDialog, public Ui::About
{
  Q_OBJECT

  public:
  About(QWidget* parent = NULL);
private slots:
  void	on_close_clicked();
};

#endif // !__ABOUT_H__
