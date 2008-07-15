//
// main.cpp for client in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Jul 15 15:09:31 2008 caner candan
// Last update Tue Jul 15 15:33:22 2008 caner candan
//

#include <QApplication>
#include "Client.h"

int	main(int ac, char **av)
{
  QApplication	app(ac, av);
  Client	client;

  client.show();
  return (app.exec());
}
