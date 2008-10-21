//
// Service.h for Service in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Mon Jul 21 02:03:48 2008 caner candan
// Last update Tue Oct 14 16:00:25 2008 caner candan
//

#ifndef __SERVICE_H__
# define __SERVICE_H__

# include <QDialog>
# include "Singleton.hpp"
# include "ui_Service.h"

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
