//
// main.cpp for client in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Jul 15 15:09:31 2008 caner candan
// Last update Sun Oct 12 17:22:42 2008 caner candan
//

#include <QApplication>
#include <QMessageBox>
#include "Database.h"
#include "Lang.h"
#include "Client.h"

int	main(int ac, char **av)
{
  QApplication	app(ac, av);
  Database*	db = Database::getInstance();

  if (!db->connect())
    {
      QMessageBox::critical(NULL, "Error database connection",
			    QString("Unable to connect to database: ")
			    + db->database().lastError().text());
      Database::kill();
      return (-1);
    }

  QSqlQuery	q(db->database());

  q.prepare("select value "
	    "from options "
	    "where key = 'lang';");
  q.exec();

  QTranslator	translator;
  QString	language;

  if (q.next())
    language = q.value(0).toString();
  else
    {
      Lang	langSet;

      if (langSet.exec() != QDialog::Accepted)
	{
	  Database::kill();
	  return (-1);
	}

      language = langSet.language->text();

      q.prepare("insert into options "
		"values('lang', ?);");
      q.addBindValue(language);
      q.exec();
    }

  translator.load(QString("../lang/client_") + language);
  app.installTranslator(&translator);

  Client	client;

  client.show();

  return (app.exec());
}
