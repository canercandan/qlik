//
// Stream.h for Stream in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Mon Aug 11 16:06:11 2008 caner candan
// Last update Mon Aug 18 16:16:35 2008 caner candan
//

#ifndef __STREAM_H__
# define __STREAM_H__

# include <QDialog>
# include "Singleton.hpp"
# include "ui_Stream.h"

class	Stream : public QDialog, public Singleton<Stream>,
		 public Ui::Stream
{
  Q_OBJECT

  friend class	Singleton<Stream>;
private slots:
private:
  Stream(QWidget* parent = NULL);
};

#endif // !__STREAM_H__
