// main.cpp --- 
// 
// Filename: main.cpp
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 01:05:39 2008 (+0200)
// Version: 
// Last-Updated: Thu Nov 27 01:05:43 2008 (+0200)
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

#include <QApplication>
#include <QMessageBox>
#include "Database.h"
#include "Lang.h"
#include "Client.h"

static bool	testDB(Database* db)
{
  if (!db->connect())
    {
      QMessageBox::critical(NULL, "Error database connection",
			    QString("Unable to connect to database: ")
			    + db->database().lastError().text());
      Database::kill();

      return (false);
    }
  return (true);
}

static bool	configLang(QApplication& app, QTranslator& translator,
			   Database* db)
{
  QSqlQuery	q(db->database());

  q.prepare("select value "
	    "from options "
	    "where key = 'lang';");
  q.exec();

  QString	language;

  if (q.next())
    language = q.value(0).toString();
  else
    {
      Lang	langSet;

      if (langSet.exec() != QDialog::Accepted)
	{
	  Database::kill();
	  return (false);
	}

      language = langSet.language->text();

      q.prepare("insert into options "
		"values('lang', ?);");
      q.addBindValue(language);
      q.exec();
    }

  translator.load(QString(":/translations/translations/client_") + language);
  app.installTranslator(&translator);

  return (true);
}

int	main(int ac, char **av)
{
  QApplication	app(ac, av);
  Database*	db = Database::getInstance();

  if (!testDB(db))
    return (-1);

  QTranslator	translator;

  if (!configLang(app, translator, db))
    return (-1);

  Client	client;

  client.show();

  return (app.exec());
}

// 
// main.cpp ends here
