//
// Accounts.cpp for Accounts in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Mon Aug 11 16:09:52 2008 caner candan
// Last update Tue Aug 19 04:06:17 2008 caner candan
//

#include <QMessageBox>
#include "Accounts.h"
#include "Database.h"

Accounts::Accounts(QWidget* parent /*= NULL*/)
  : QDialog(parent)
{
  setupUi(this);
  reset();
  connect(showPassword, SIGNAL(stateChanged(int)),
	  this, SLOT(_modifyPassword(int)));
}

void	Accounts::reset()
{
  this->_loadList();
  this->_resetAccount();
}

void	Accounts::on_save_clicked()
{
  if (this->accountsList->currentRow() < 0)
    return;
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

  QSqlQuery	q(Database::getInstance()->database());

  q.prepare("update users "
	    "set username = ?, password = ? "
	    "where id = ?;");
  q.addBindValue(this->username->text());
  q.addBindValue(this->password->text());
  q.addBindValue(this->accountsList->currentItem()->data(Qt::UserRole));
  q.exec();
  this->_resetAccount();
  this->_loadList();
}

void	Accounts::on_done_clicked()
{
  this->hide();
}

void	Accounts::on_manage_clicked()
{
  this->_loadAccount();
}

void	Accounts::on_add_clicked()
{
  QSqlQuery	q(Database::getInstance()->database());

  q.prepare("insert into users "
	    "values(null, 'new account', '');");
  q.exec();
  this->_resetAccount();
  this->_loadList();
}

void	Accounts::on_del_clicked()
{
  if (this->accountsList->currentRow() < 0)
    return;
  if (QMessageBox::question(this,
			    tr("Are you sure ?"),
			    tr("Are you sure ?"),
			    QMessageBox::Yes | QMessageBox::No)
      != QMessageBox::Yes)
    return;

  QSqlQuery	q(Database::getInstance()->database());

  q.prepare("delete from users "
	    "where id = ?;");
  q.addBindValue(this->accountsList->currentItem()->data(Qt::UserRole));
  q.exec();
  this->_resetAccount();
  this->_loadList();
}

void	Accounts::_loadList()
{
  QSqlQuery		q(Database::getInstance()->database());
  QListWidgetItem*	item;

  q.prepare("select id, username "
	    "from users;");
  q.exec();
  this->accountsList->clear();
  while (q.next())
    {
      item = new QListWidgetItem;
      item->setIcon(QIcon("images/user.png"));
      item->setText(q.value(1).toString());
      item->setData(Qt::UserRole, q.value(0).toString());
      this->accountsList->addItem(item);
    }
}

void	Accounts::_loadAccount()
{
  if (this->accountsList->currentRow() < 0)
    return;

  QSqlQuery	q(Database::getInstance()->database());

  q.prepare("select username, password "
	    "from users "
	    "where id = ?;");
  q.addBindValue(this->accountsList->currentItem()->data(Qt::UserRole));
  q.exec();
  if (q.next())
    {
      this->username->setText(q.value(0).toString());
      this->username->setEnabled(true);
      this->password->setText(q.value(1).toString());
      this->password->setEnabled(true);
      this->save->setEnabled(true);
    }
}

void	Accounts::_resetAccount()
{
  this->username->setText("");
  this->username->setEnabled(false);
  this->password->setText("");
  this->password->setEnabled(false);
  this->save->setEnabled(false);
}

void	Accounts::_modifyPassword(int state)
{
  if (state == Qt::Checked)
    this->password->setEchoMode(QLineEdit::Normal);
  else
    this->password->setEchoMode(QLineEdit::Password);
}
