// Database.h --- 
// 
// Filename: Database.h
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 00:55:40 2008 (+0200)
// Version: 
// Last-Updated: Thu Nov 27 00:55:46 2008 (+0200)
//           By: Caner Candan
//     Update #: 2
// URL: 
// Keywords: 
// Compatibility: 
// 
// 

// Commentary: 
// 
// 
// 
// 

// Change log:
// 
// 
// 
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 3, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; see the file COPYING.  If not, write to
// the Free Software Foundation, Inc., 51 Franklin Street, Fifth
// Floor, Boston, MA 02110-1301, USA.

// 
// 

// Code:

#ifndef __DATABASE_H__
# define __DATABASE_H__

# include <QtSql>
# include "Singleton.hpp"

# define DBFILE	"client.db"

class	Database : public Singleton<Database>
{
  friend class	Singleton<Database>;
public:
  const QSqlDatabase&	database();

  bool	connect();
  void	close();
private:
  Database();
  ~Database();
private:
  QSqlDatabase	_db;
};

#endif // !__DATABASE_H__

// 
// Database.h ends here
