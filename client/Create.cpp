//
// Create.cpp for Create in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Jul 15 18:46:22 2008 caner candan
// Last update Tue Aug 19 04:21:05 2008 caner candan
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
  if (this->username->text().isEmpty())
    {
      QMessageBox::information(this,
			       tr("No username"),
			       tr("Please insert your username"));
      this->username->setFocus();
      return;
    }

  QRegExp	rx("^[a-zA-Z][a-zA-Z0-9-_]{3,19}$");

  if (rx.indexIn(this->username->text()) < 0)
    {
      QMessageBox::information(this,
			       tr("Username incorrect"),
			       tr("Username incorrect"));
      this->username->setFocus();
      return;
    }
  if (QMessageBox::question(this,
			    tr("Are you sure ?"),
			    tr("Are you sure ?"),
			    QMessageBox::Yes | QMessageBox::No)
      != QMessageBox::Yes)
    return;
  this->accept();
}

void	Create::on_pushButtonCancel_clicked()
{
  this->reject();
}
