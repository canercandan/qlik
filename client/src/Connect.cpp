//
// Connect.cpp for Connect in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Jul 15 18:46:22 2008 caner candan
// Last update Wed Aug 20 07:38:06 2008 caner candan
//

#include <QWidget>
#include <QMessageBox>
#include "Connect.h"
#include "Database.h"

Connect::Connect(QWidget *parent /*= NULL*/)
  : QDialog(parent)
{
  setupUi(this);
  _loadAccounts();
}

Connect::~Connect()
{}

void	Connect::on_pushButtonOk_clicked()
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
