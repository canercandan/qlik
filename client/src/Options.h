//
// Options.h for Options in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Mon Aug 11 16:06:11 2008 caner candan
// Last update Thu Oct 16 15:24:57 2008 caner candan
//

#ifndef __OPTIONS_H__
# define __OPTIONS_H__

# include <QDialog>
# include "Singleton.hpp"
# include "ui_Options.h"

# define OPT_VERBOSE	1 << 1
# define OPT_SECURE	1 << 2
# define OPT_SPLASH	1 << 3

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
