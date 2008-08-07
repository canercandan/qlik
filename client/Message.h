//
// Message.h for Message in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Mon Aug  4 06:09:17 2008 caner candan
// Last update Tue Aug  5 21:29:01 2008 caner candan
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
  ~Message();
private slots:
  void	on_send_clicked();
};

#endif // !__MESSAGE_H__
