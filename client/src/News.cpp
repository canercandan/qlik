//
// News.cpp for client in /home/candan_c/cu/rendu/qlik/client/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sat Nov 22 01:07:00 2008 caner candan
// Last update Mon Nov 24 01:02:26 2008 caner candan
//

#include "News.h"
#include "Client.h"
#include "Socket.h"
#include "Protocole.h"

News::News(QWidget* parent /*= NULL*/)
  : QDialog(parent)
{
  setupUi(this);

  Client*	client = static_cast<Client*>(parent);
  bool		rightAdmin = (client->getRight() & RIGHT_ADMIN);

  addSubject->setEnabled(rightAdmin);
  addBody->setEnabled(rightAdmin);
  addOk->setEnabled(rightAdmin);
}

void	News::on_readClose_clicked()
{
  this->hide();
}

void	News::on_addOk_clicked()
{
  QTextStream	stream(Socket::getInstance()->socket());

  stream << NEWS_ADD
	 << SP << this->addSubject->text()
	 << SP << this->addBody->toPlainText()
	 << NL;
}

void	News::on_addCancel_clicked()
{
  this->hide();
}
