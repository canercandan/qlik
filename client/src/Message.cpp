//
// Message.cpp for Message in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Mon Aug  4 06:10:50 2008 caner candan
// Last update Sun Nov 23 23:39:39 2008 caner candan
//

#include <QWidget>
#include <QMessageBox>
#include "Message.h"
#include "Client.h"
#include "Socket.h"
#include "Contact.h"
#include "Protocole.h"

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

  stream << MESSAGE << SP << to << SP << edit << NL;

  static_cast<Client*>(this->parent())->appendMessage(to, from, edit);

  this->edit->clear();
  this->edit->setFocus();
}

void	Message::on_add_clicked()
{
  Contact	contact;

  contact.username->setText(this->to->text());
  contact.alias->setFocus();

  if (contact.exec() != QDialog::Accepted)
    return;

  static_cast<Client*>(this->parent())->addToContactsList(contact);
}
