//
// Create.cpp for Create in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Jul 15 18:46:22 2008 caner candan
// Last update Fri Aug  8 09:03:45 2008 caner candan
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
  QRegExp	rx;

  if (this->username->text().isEmpty())
    {
      QMessageBox::information(this,
			       tr("No username"),
			       tr("Please insert your username"));
      this->username->setFocus();
      return;
    }
  rx.setPattern("^[a-zA-Z0-9-_]{4,20}$");
  if (rx.indexIn(this->username->text()) < 0)
    {
      QMessageBox::information(this,
			       tr("Username incorrect"),
			       tr("Username incorrect"));
      this->username->setFocus();
      return;
    }
  if (this->password->text().isEmpty())
    {
      QMessageBox::information(this,
			       tr("No password"),
			       tr("Please insert your password"));
      this->password->setFocus();
      return;
    }
  rx.setPattern("^[a-zA-Z0-9-_$/()&%^#]{4,20}$");
  if (rx.indexIn(this->password->text()) < 0)
    {
      QMessageBox::information(this,
			       tr("Password incorrect"),
			       tr("Password incorrect"));
      this->password->setFocus();
      return;
    }
  if (this->repassword->text().isEmpty())
    {
      QMessageBox::information(this,
			       tr("No password repeated"),
			       tr("Please repeat your password"));
      this->repassword->setFocus();
      return;
    }
  if (this->password->text() != this->repassword->text())
    {
      QMessageBox::information(this,
			       tr("Password is different to repeated password"),
			       tr("Please insert the same password"));
      this->password->setFocus();
      return;
    }
  this->accept();
}

void	Create::on_pushButtonCancel_clicked()
{
  this->reject();
}
