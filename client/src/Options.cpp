//
// Options.cpp for Options in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Mon Aug 11 16:09:52 2008 caner candan
// Last update Mon Aug 18 19:39:21 2008 caner candan
//

#include "Options.h"
#include "Database.h"
#include "Socket.h"
#include "Client.h"

Options::Options(QWidget* parent /*= NULL*/)
  : QDialog(parent)
{
  setupUi(this);
  _fillFields();
  _connectToSocket();
}

void	Options::on_reconnect_clicked()
{
  static_cast<Client*>(this->parent())->logout();
  this->_connectToSocket();
  this->on_save_clicked();
}

void	Options::on_save_clicked()
{
  this->_modifyServer();
  this->hide();
}

void	Options::on_cancel_clicked()
{
  this->hide();
}

void	Options::_connectToSocket()
{
  Socket::getInstance()->connect(this->host->text(),
				 this->port->text().toInt());
}

void	Options::_fillFields()
{
  QSqlQuery	q(Database::getInstance()->database());

  q.prepare("select key, value "
	    "from options "
	    "where key in ('host', 'port');");
  q.exec();
  while (q.next())
    {
      if (q.value(0).toString() == "host")
	this->host->setText(q.value(1).toString());
      else if (q.value(0).toString() == "port")
	this->port->setText(q.value(1).toString());
    }
}

void	Options::_modifyServer()
{
  QSqlQuery	q(Database::getInstance()->database());

  q.prepare("update options "
	    "set value = ? "
	    "where key = 'host';");
  q.addBindValue(this->host->text());
  q.exec();
  q.prepare("update options "
	    "set value = ? "
	    "where key = 'port';");
  q.addBindValue(this->port->text());
  q.exec();
}
