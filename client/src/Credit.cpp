//
// Credit.cpp for Credit in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Mon Aug 11 16:09:52 2008 caner candan
// Last update Sun Oct 12 14:23:03 2008 caner candan
//

#include <QMessageBox>
#include "Credit.h"
#include "Client.h"
#include "Socket.h"
#include "Protocole.h"

Credit::Credit(QWidget* parent /*= NULL*/)
  : QDialog(parent)
{
  setupUi(this);
  reset();
}

void	Credit::reset()
{
  this->currently->setText(static_cast<Client*>
			   (this->parent())->creditCurrently->text());
}

void	Credit::on_buy_clicked()
{
  if (QMessageBox::question(this, tr("buy"), tr("buy_txt"),
			    QMessageBox::Ok | QMessageBox::Cancel)
      != QMessageBox::Ok)
    return;

  QTextStream	stream(Socket::getInstance()->socket());

  stream << MESSAGE << ' ' << "finance" << ' '
	 << tr("notice_add_txt")
	 << this->coins->currentText()
	 << tr("notice_add_txt2")
	 << endl;
  QMessageBox::information(this, tr("notification"),
			   tr("notification_txt"));
  this->hide();
}

void	Credit::on_cancel_clicked()
{
  this->hide();
}
