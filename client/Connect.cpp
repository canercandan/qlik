//
// Connect.cpp for Connect in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Jul 15 18:46:22 2008 caner candan
// Last update Tue Jul 15 19:31:41 2008 caner candan
//

#include <QWidget>
#include <QMessageBox>
#include "Connect.h"

Connect::Connect(QWidget *parent /*= NULL*/)
  : QDialog(parent)
{
  setupUi(this);
}

Connect::~Connect()
{}

void	Connect::on_pushButtonOk_clicked()
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
  else
    this->accept();
}

void	Connect::on_pushButtonCancel_clicked()
{
  this->reject();
}
