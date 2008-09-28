//
// Contact.cpp for Contact in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Jul 15 18:46:22 2008 caner candan
// Last update Tue Aug 19 23:51:52 2008 caner candan
//

#include <QWidget>
#include <QMessageBox>
#include "Contact.h"

Contact::Contact(QWidget *parent /*= NULL*/)
  : QDialog(parent)
{
  setupUi(this);
}

void	Contact::on_ok_clicked()
{
  if (this->username->text().isEmpty())
    {
      QMessageBox::information(this,
			       tr("No username"),
			       tr("Please insert the username"));
      this->username->setFocus();
      return;
    }

  QRegExp	rx;

  rx.setPattern("^[a-zA-Z][a-zA-Z0-9-_]{3,19}$");
  if (rx.indexIn(this->username->text()) < 0)
    {
      QMessageBox::information(this,
			       tr("Username incorrect"),
			       tr("Username incorrect"));
      this->username->setFocus();
      return;
    }
  if (!this->alias->text().isEmpty())
    {
      rx.setPattern("^[a-zA-Z0-9-_ ]{4,20}$");
      if (rx.indexIn(this->alias->text()) < 0)
	{
	  QMessageBox::information(this,
				   tr("Alias incorrect"),
				   tr("Alias incorrect"));
	  this->alias->setFocus();
	  return;
	}
    }
  this->accept();
}

void	Contact::on_cancel_clicked()
{
  this->reject();
}
