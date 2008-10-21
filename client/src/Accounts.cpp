//
// Accounts.cpp for Accounts in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Mon Aug 11 16:09:52 2008 caner candan
// Last update Tue Oct 14 16:13:29 2008 caner candan
//

#include <QMessageBox>
#include "Accounts.h"
#include "Database.h"
#include "Protocole.h"

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
      QMessageBox::information(this, tr("no_username"),
			       tr("no_username_txt"));
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

  QSqlQuery	q(Database::getInstance()->database());

  q.prepare("update users "
	    "set username = ?, password = ? "
	    "where username = ?;");
  q.addBindValue(this->username->text());
  q.addBindValue(this->password->text());
  q.addBindValue(this->accountsList->currentItem()->text());
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
	    "values('new account', '');");
  q.exec();

  this->_resetAccount();
  this->_loadList();
}

void	Accounts::on_del_clicked()
{
  if (this->accountsList->currentRow() < 0)
    return;
  if (QMessageBox::question(this,
			    tr("are_you_sure"),
			    tr("are_you_sure_txt"),
			    QMessageBox::Yes | QMessageBox::No)
      != QMessageBox::Yes)
    return;

  QSqlQuery	q(Database::getInstance()->database());

  q.prepare("delete from users "
	    "where username = ?;");
  q.addBindValue(this->accountsList->currentItem()->text());
  q.exec();

  this->_resetAccount();
  this->_loadList();
}

void	Accounts::_loadList()
{
  QSqlQuery		q(Database::getInstance()->database());
  QListWidgetItem*	item;

  q.prepare("select username "
	    "from users;");
  q.exec();
  this->accountsList->clear();
  while (q.next())
    {
      item = new QListWidgetItem;
      item->setIcon(QIcon("images/user.png"));
      item->setText(q.value(0).toString());
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
	    "where username = ?;");
  q.addBindValue(this->accountsList->currentItem()->text());
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
