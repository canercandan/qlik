//
// Message.h for Message in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Mon Aug  4 06:09:17 2008 caner candan
// Last update Mon Sep 29 19:57:08 2008 caner candan
//

#ifndef __MESSAGE_H__
# define __MESSAGE_H__

# include <QDialog>
# include "ui_Message.h"

class	Message : public QDialog, public Ui::Message
{
  Q_OBJECT

  public:
  Message(QWidget* parent = NULL);
private slots:
  void	on_send_clicked();
  void	on_add_clicked();
};

#endif // !__MESSAGE_H__
