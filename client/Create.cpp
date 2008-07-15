//
// Create.cpp for Create in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Jul 15 18:46:22 2008 caner candan
// Last update Tue Jul 15 22:04:24 2008 caner candan
//

#include <QWidget>
#include <QMessageBox>
#include "Create.h"

Create::Create(QWidget *parent /*= NULL*/)
  : QDialog(parent)
{
  setupUi(this);
}

Create::~Create()
{}

void	Create::on_pushButtonOk_clicked()
{
  if (this->address->text().isEmpty())
    {
      QMessageBox::information(this,
			       tr("No address"),
			       tr("Please insert an address to connect"));
      this->address->setFocus();
    }
  else if (this->port->text().isEmpty())
    {
      QMessageBox::information(this,
			       tr("No port"),
			       tr("Please insert a port to connect"));
      this->port->setFocus();
    }
  else if (this->username->text().isEmpty())
    {
      QMessageBox::information(this,
			       tr("No username"),
			       tr("Please insert your username"));
      this->username->setFocus();
    }
  else if (this->password->text().isEmpty())
    {
      QMessageBox::information(this,
			       tr("No password"),
			       tr("Please insert your password"));
      this->password->setFocus();
    }
  else if (this->repassword->text().isEmpty())
    {
      QMessageBox::information(this,
			       tr("No password repeated"),
			       tr("Please repeat your password"));
      this->repassword->setFocus();
    }
  else if (this->password->text() != this->repassword->text())
    {
      QMessageBox::information(this,
			       tr("Password is different to repeated password"),
			       tr("Please insert the same password"));
      this->password->setFocus();
    }
  else
    this->accept();
}

void	Create::on_pushButtonCancel_clicked()
{
  this->reject();
}
