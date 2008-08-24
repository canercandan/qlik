//
// Message.cpp for Message in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Mon Aug  4 06:10:50 2008 caner candan
// Last update Tue Aug 19 08:40:35 2008 caner candan
//

#include <QWidget>
#include <QMessageBox>
#include "Message.h"
#include "Client.h"
#include "Socket.h"

Message::Message(QWidget* parent /*= NULL*/)
  : QDialog(parent)
{
  setupUi(this);
}

void	Message::on_send_clicked()
{
  QTextStream		stream(Socket::getInstance()->socket());
  const QString&	from = this->from->text();
  const QString&	to = this->to->text();
  const QString&	edit = this->edit->text();

  if (edit.isEmpty())
    return;
  stream << MESSAGE << ' ' << to << ' ' << edit << endl;
  static_cast<Client*>(this->parent())->appendMessage(to, from, edit);
  this->edit->clear();
  this->edit->setFocus();
}
