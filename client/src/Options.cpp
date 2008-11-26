// Options.cpp --- 
// 
// Filename: Options.cpp
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 00:58:56 2008 (+0200)
// Version: 
// Last-Updated: Thu Nov 27 00:59:02 2008 (+0200)
//           By: Caner Candan
//     Update #: 1
// URL: 
// Keywords: 
// Compatibility: 
// 
// 

// Commentary: 
// 
// 
// 
// 

// Change log:
// 
// 
// 
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 3, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; see the file COPYING.  If not, write to
// the Free Software Foundation, Inc., 51 Franklin Street, Fifth
// Floor, Boston, MA 02110-1301, USA.

// 
// 

// Code:

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
	    "where key in ('host', 'port', 'mask', 'lang');");
  q.exec();

  while (q.next())
    {
      QString	name(q.value(0).toString());
      QString	value(q.value(1).toString());

      if (name == "host")
	this->host->setText(value);
      else if (name == "port")
	this->port->setText(value);
      else if (name == "mask")
	{
	  int	value = q.value(1).toInt();

	  if (value & OPT_VERBOSE)
	    this->verbose->setChecked(true);
	  if (value & OPT_SECURE)
	    this->secure->setChecked(true);
	  if (value & OPT_SPLASH)
	    this->splash->setChecked(true);
	}
      else if (name == "lang")
	this->language->setText(value);
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

  int	mask = 0;

  if (this->verbose->isChecked())
    mask |= OPT_VERBOSE;
  if (this->secure->isChecked())
    mask |= OPT_SECURE;
  if (this->splash->isChecked())
    mask |= OPT_SPLASH;

  q.prepare("update options "
	    "set value = ? "
	    "where key = 'mask';");
  q.addBindValue(mask);
  q.exec();

  q.prepare("update options "
	    "set value = ? "
	    "where key = 'lang';");
  q.addBindValue(this->language->text());
  q.exec();
}

// 
// Options.cpp ends here
