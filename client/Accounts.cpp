//
// Accounts.cpp for Accounts in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Mon Aug 11 16:09:52 2008 caner candan
// Last update Mon Aug 18 21:06:15 2008 caner candan
//

#include <QMessageBox>
#include "Accounts.h"
#include "Database.h"

Accounts::Accounts(QWidget* parent /*= NULL*/)
  : QDialog(parent)
{
  setupUi(this);
  _loadList();
  connect(accountsList, SIGNAL(currentRowChanged(int)),
	  this, SLOT(_loadAccount(int)));
}

void	Accounts::on_save_clicked()
{
  QSqlQuery	q(Database::getInstance()->database());

  QMessageBox::information(this,
			   tr("save ok"),
			   tr("save ok"));
}

void	Accounts::on_done_clicked()
{
  this->hide();
}

void	Accounts::on_add_clicked()
{
  QSqlQuery	q(Database::getInstance()->database());

  q.prepare("insert into users "
	    "values(null, 'new account', '');");
  q.exec();
  this->_loadList();
}

void	Accounts::on_del_clicked()
{
  if (this->accountsList->currentRow() < 0)
    return;

  QSqlQuery	q(Database::getInstance()->database());

  q.prepare("delete from users "
	    "where id = ?;");
  q.addBindValue(this->accountsList->currentItem()->data(Qt::UserRole));
  q.exec();
  this->_loadList();
  QMessageBox::information(this,
			   tr("del account"),
			   tr("del account"));
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

void	Accounts::_loadAccount(int row)
{
  QSqlQuery	q(Database::getInstance()->database());

  q.prepare("select username, password "
	    "from users "
	    "where id = ? "
	    "limit 1;");
  q.addBindValue(this->accountsList->item(row)->data(Qt::UserRole));
  q.exec();
  if (q.next())
    {
      this->username->setText(q.value(0).toString());
      this->username->setEnabled(true);
      this->password->setText(q.value(1).toString());
      this->password->setEnabled(true);
    }
}
