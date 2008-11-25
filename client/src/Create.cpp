//
// Create.cpp for Create in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Jul 15 18:46:22 2008 caner candan
// Last update Sat Nov 22 01:04:07 2008 caner candan
//

#include <QWidget>
#include <QMessageBox>
#include "Create.h"
#include "Protocole.h"

Create::Create(QWidget* parent /*= NULL*/)
  : QDialog(parent)
{
  setupUi(this);
}

Create::~Create()
{}

void	Create::on_ok_clicked()
{
  if (this->username->text().isEmpty())
    {
      QMessageBox::information(this, tr("no_username"), tr("no_username_txt"));
      this->username->setFocus();
      return;
    }

  QRegExp	rx(PATTERN_USERNAME);

  if (rx.indexIn(this->username->text()) < 0)
    {
      QMessageBox::information(this, tr("username_inc"),
			       tr("username_inc_txt"));
      this->username->setFocus();
      return;
    }

  if (QMessageBox::question(this, tr("are_you_sure"),
			    tr("are_you_sure_txt"),
			    QMessageBox::Yes | QMessageBox::No)
      != QMessageBox::Yes)
    return;
  this->accept();
}

void	Create::on_cancel_clicked()
{
  this->reject();
}
