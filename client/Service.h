//
// Service.h for Service in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Mon Jul 21 02:03:48 2008 caner candan
// Last update Mon Jul 21 02:04:55 2008 caner candan
//

#ifndef __SERVICE_H__
# define __SERVICE_H__

# include <QDialog>
# include "ui_Service.h"

class	Service : public QDialog, public Ui::Service
{
  Q_OBJECT

  public:
  Service(QWidget* parent = NULL);
  ~Service();
private slots:
};

#endif // !__SERVICE_H__
