//
// Lang.cpp for client in /home/candan_c/cu/rendu/ekzay/client/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sun Oct 12 16:14:37 2008 caner candan
// Last update Sun Oct 12 16:39:05 2008 caner candan
//

#include "Lang.h"
#include "Database.h"

Lang::Lang(QWidget* parent /*= NULL*/)
  : QDialog(parent)
{
  setupUi(this);
  language->setText(QLocale::system().name());
}

void	Lang::on_save_clicked()
{
  this->accept();
}
