//
// Stream.h for Stream in /home/candan_c/rendu/ekzay/client
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Mon Aug 11 16:06:11 2008 caner candan
// Last update Mon Aug 11 16:09:32 2008 caner candan
//

#ifndef __STREAM_H__
# define __STREAM_H__

# include <QDialog>
# include "ui_Stream.h"

class	Stream : public QDialog, public Ui::Stream
{
  Q_OBJECT

  public:
  Stream(QWidget* parent = NULL);
  ~Stream();
private slots:  
};

#endif // !__STREAM_H__
