//
// Credit.cpp for Credit in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Mon Aug 11 16:09:52 2008 caner candan
// Last update Tue Aug 19 16:20:04 2008 caner candan
//

#include <QMessageBox>
#include "Credit.h"
#include "Client.h"
#include "Socket.h"

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
  if (QMessageBox::question(this,
			    tr("buy"),
			    tr("Go to this link: "
			       "http://www.paypal.com\n"
			       "When you have finish your payment"
			       ", click on Ok to notice one\n"
			       "or if you want to cancel click on Cancel."),
			    QMessageBox::Ok | QMessageBox::Cancel)
      != QMessageBox::Ok)
    return;

  QTextStream	stream(Socket::getInstance()->socket());

  stream << MESSAGE
	 << ' ' << "finance"
	 << ' ' << "Notice: add " << this->coins->currentText()
	 << " coins."
	 << endl;
  QMessageBox::information(this,
			   tr("Notification"),
			   tr("Your notice has been send success.\n"
			      "After check you will receive your coins "
			      "in your accounts."));
  this->hide();
}

void	Credit::on_cancel_clicked()
{
  this->hide();
}
