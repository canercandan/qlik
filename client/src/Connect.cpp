//
// Connect.cpp for Connect in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Jul 15 18:46:22 2008 caner candan
// Last update Sat Nov 22 01:02:21 2008 caner candan
//

#include <QMessageBox>
#include "Connect.h"
#include "Database.h"
#include "Protocole.h"

Connect::Connect(QWidget* parent /*= NULL*/)
  : QDialog(parent)
{
  setupUi(this);
  _loadAccounts();
}

void	Connect::on_ok_clicked()
{
  if (!this->connectBox->currentIndex()) // accounts
    {
      QSqlQuery	q(Database::getInstance()->database());

      q.prepare("select username, password "
		"from users "
		"where username = ?;");
      q.addBindValue(this->accounts->currentText());
      q.exec();
      if (q.next())
	{
	  this->username->setText(q.value(0).toString());
	  this->password->setText(q.value(1).toString());
	}
    }
  if (this->username->text().isEmpty())
    {
      QMessageBox::information(this, tr("no_username"), tr("no_username_txt"));
      this->username->setFocus();
      return;
    }

  QRegExp	rx;

  rx.setPattern(PATTERN_USERNAME);

  if (rx.indexIn(this->username->text()) < 0)
    {
      QMessageBox::information(this, tr("username_inc"),
			       tr("username_inc_txt"));
      this->username->setFocus();
      return;
    }

  if (this->password->text().isEmpty())
    {
      QMessageBox::information(this, tr("no_password"),
			       tr("no_password_txt"));
      this->password->setFocus();
      return;
    }

  rx.setPattern(PATTERN_PASSWD);

  if (rx.indexIn(this->password->text()) < 0)
    {
      QMessageBox::information(this, tr("password_inc"),
			       tr("password_inc_txt"));
      this->password->setFocus();
      return;
    }
  this->accept();
}

void	Connect::on_cancel_clicked()
{
  this->reject();
}

void	Connect::_loadAccounts()
{
  QSqlQuery	q(Database::getInstance()->database());

  q.prepare("select username "
	    "from users;");
  q.exec();

  this->accounts->clear();
  while (q.next())
    this->accounts->addItem(q.value(0).toString());
}
