//
// Contact.h for Contact in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Jul 15 18:36:03 2008 caner candan
// Last update Tue Aug 19 19:04:55 2008 caner candan
//

#ifndef __CONTACT_H__
# define __CONTACT_H__

# include <QDialog>
# include "ui_Contact.h"

class	Contact : public QDialog, public Ui::Contact
{
  Q_OBJECT

  public:
  Contact(QWidget *parent = NULL);
private slots:
  void	on_ok_clicked();
  void	on_cancel_clicked();
};

#endif // !__CONTACT_H__
