//
// Options.h for Options in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Mon Aug 11 16:06:11 2008 caner candan
// Last update Mon Aug 18 19:38:55 2008 caner candan
//

#ifndef __OPTIONS_H__
# define __OPTIONS_H__

# include <QDialog>
# include "Singleton.hpp"
# include "ui_Options.h"

class	Options : public QDialog, public Singleton<Options>,
		  public Ui::Options
{
  Q_OBJECT

  friend class	Singleton<Options>;
private slots:
  void	on_reconnect_clicked();
  void	on_save_clicked();
  void	on_cancel_clicked();
private:
  Options(QWidget* parent = NULL);

  void	_connectToSocket();
  void	_fillFields();
  void	_modifyServer();
};

#endif // !__OPTIONS_H__
