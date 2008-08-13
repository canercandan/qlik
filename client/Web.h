//
// Web.h for Web in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Mon Aug 11 16:06:11 2008 caner candan
// Last update Mon Aug 11 16:08:54 2008 caner candan
//

#ifndef __WEB_H__
# define __WEB_H__

# include <QDialog>
# include "ui_Web.h"

class	Web : public QDialog, public Ui::Web
{
  Q_OBJECT

  public:
  Web(QWidget* parent = NULL);
  ~Web();
private slots:  
};

#endif // !__WEB_H__
