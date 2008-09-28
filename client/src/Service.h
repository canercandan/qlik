//
// Service.h for Service in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Mon Jul 21 02:03:48 2008 caner candan
// Last update Tue Sep  2 00:03:54 2008 caner candan
//

#ifndef __SERVICE_H__
# define __SERVICE_H__

# include <QDialog>
# include "Singleton.hpp"
# include "ui_Service.h"

# define PATTERN_NAME	"^[a-zA-Z0-9-_]+$"
# define PATTERN_DOMAIN	"^(www.)?[a-z0-9-_]+\\.[a-z]{2,4}$"

class	Service : public QDialog, public Singleton<Service>,
		  public Ui::Service
{
  Q_OBJECT

  friend class	Singleton<Service>;
public:
  void	createWebOffer();
  void	createStreamOffer();
  void	createWebMore();
  void	createStreamMore();
private slots:
  void	on_ok_clicked();
  void	on_cancel_clicked();
private:
  Service(QWidget* parent = NULL);

  bool	_confirmOffer(QListWidget*);
  bool	_confirmMore(QComboBox* list1, int ratio1,
		     QComboBox* list2, int ratio2);
};

#endif // !__SERVICE_H__