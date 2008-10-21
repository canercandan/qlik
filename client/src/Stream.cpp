//
// Stream.cpp for Stream in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Mon Aug 11 16:09:52 2008 caner candan
// Last update Mon Oct 13 01:10:02 2008 caner candan
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

  stream << STREAM_START
	 << ' ' << this->name->text()
	 << endl;
}

void	Stream::on_stop_clicked()
{
  QTextStream	stream(Socket::getInstance()->socket());

  stream << STREAM_STOP
	 << ' ' << this->name->text()
	 << endl;
}
