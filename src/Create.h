//
// Create.h for Create in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Tue Jul 15 18:36:03 2008 caner candan
// Last update Tue Jul 15 23:20:06 2008 caner candan
//

#ifndef __CREATE_H__
# define __CREATE_H__

# include <QDialog>
# include "ui_Create.h"

class	Create : public QDialog, public Ui::Create
{
  Q_OBJECT

  public:
  Create(QWidget *parent = NULL);
  ~Create();
private slots:
  void	on_pushButtonOk_clicked();
  void	on_pushButtonCancel_clicked();
private:
};

#endif // !__CREATE_H__
