//
// Lang.h for client in /home/candan_c/cu/rendu/ekzay/client/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Oct 12 16:11:58 2008 caner candan
// Last update Sun Oct 12 16:39:06 2008 caner candan
//

#ifndef __LANG_H__
# define __LANG_H__

# include <QDialog>
# include "ui_Lang.h"

class	Lang : public QDialog, public Ui::Lang
{
  Q_OBJECT

  public:
  Lang(QWidget* parent = NULL);
private slots:
  void	on_save_clicked();
};

#endif // !__LANG_H__
