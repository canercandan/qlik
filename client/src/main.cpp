//
// main.cpp for client in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Jul 15 15:09:31 2008 caner candan
// Last update Wed Nov 26 02:36:45 2008 caner candan
//

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

static bool	configLang(QApplication& app, Database* db)
{
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

  if (!configLang(app, db))
    return (-1);

  Client	client;

  client.show();

  return (app.exec());
}
