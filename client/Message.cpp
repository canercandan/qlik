//
// Message.cpp for Message in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Mon Aug  4 06:10:50 2008 caner candan
// Last update Tue Aug  5 21:29:11 2008 caner candan
//

#include <QWidget>
#include <QMessageBox>
#include "Message.h"
#include "Client.h"

Message::Message(QWidget* parent /*= NULL*/)
  : QDialog(parent)
{
  setupUi(this);
}

Message::~Message()
{}

void	Message::on_send_clicked()
{
  ((Client*)this->parentWidget())->sendMessage(this);
}
