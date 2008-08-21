//
// Connect.cpp for Connect in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Jul 15 18:46:22 2008 caner candan
// Last update Mon Aug 18 21:36:08 2008 caner candan
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
  if (this->username->text().isEmpty())
    {
      QMessageBox::information(this,
			       tr("No username"),
			       tr("Please insert your username"));
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
  if (this->password->text().isEmpty())
    {
      QMessageBox::information(this,
			       tr("No password"),
			       tr("Please insert your password"));
      this->password->setFocus();
      return;
    }
  rx.setPattern("^[a-zA-Z0-9!\"#$%&'()*+,-./:;<=>?[\\]^_`{|}~]{4,20}$");
  if (rx.indexIn(this->password->text()) < 0)
    {
      QMessageBox::information(this,
			       tr("Password incorrect"),
			       tr("Password incorrect"));
      this->password->setFocus();
      return;
    }
  this->accept();
}

void	Connect::on_pushButtonCancel_clicked()
{
  this->reject();
}
