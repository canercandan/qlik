//
// Stream.cpp for Stream in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Mon Aug 11 16:09:52 2008 caner candan
// Last update Sun Nov 23 23:37:56 2008 caner candan
//

#include <QTextStream>
#include "Stream.h"
#include "Socket.h"
#include "Protocole.h"

Stream::Stream(QWidget* parent /*= NULL*/)
  : QDialog(parent)
{
  setupUi(this);
}

void	Stream::on_start_clicked()
{
  QTextStream	stream(Socket::getInstance()->socket());

  stream << STREAM_START << SP << this->name->text() << NL;
}

void	Stream::on_stop_clicked()
{
  QTextStream	stream(Socket::getInstance()->socket());

  stream << STREAM_STOP << SP << this->name->text() << NL;
}
