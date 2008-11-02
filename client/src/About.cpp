//
// About.cpp for client in /home/candan_c/cu/rendu/ekzay/client/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Oct 14 19:08:15 2008 caner candan
// Last update Tue Oct 14 23:59:59 2008 caner candan
//

#include "About.h"

About::About(QWidget* parent /*= NULL*/)
  : QDialog(parent)
{
  setupUi(this);
}

void	About::on_close_clicked()
{
  this->accept();
}
