//
// Web.h for Web in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Mon Aug 11 16:06:11 2008 caner candan
// Last update Mon Aug 18 16:16:29 2008 caner candan
//

#ifndef __WEB_H__
# define __WEB_H__

# include <QDialog>
# include "Singleton.hpp"
# include "ui_Web.h"

class	Web : public QDialog, public Singleton<Web>,
	      public Ui::Web
{
  Q_OBJECT

  friend class	Singleton<Web>;
private slots:
private:
  Web(QWidget* parent = NULL);
};

#endif // !__WEB_H__
