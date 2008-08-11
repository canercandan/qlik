//
// Service.h for Service in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Mon Jul 21 02:03:48 2008 caner candan
// Last update Fri Aug  8 15:30:53 2008 caner candan
//

#ifndef __SERVICE_H__
# define __SERVICE_H__

# include <QDialog>
# include "ui_Service.h"

# define PATTERN_NAME	"^[a-zA-Z0-9-_]+$"
# define PATTERN_DOMAIN	"^(www.)?[a-z0-9-_]+\\.[a-z]{2,4}$"

class	Service : public QDialog, public Ui::Service
{
  Q_OBJECT

  public:
  Service(QWidget* parent = NULL);
  ~Service();

  void	createWebOffer();
  void	createStreamOffer();
  void	createWebMore();
  void	createStreamMore();
private slots:
  void	on_ok_clicked();
  void	on_cancel_clicked();
};

#endif // !__SERVICE_H__
