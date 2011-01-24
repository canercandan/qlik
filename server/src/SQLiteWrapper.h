// SQLiteWrapper.h --- 
// 
// Filename: SQLiteWrapper.h
// Description: 
// Author: Caner Candan
// Maintainer: 
// Created: Thu Nov 27 09:14:05 2008 (+0200)
// Version: 
// Last-Updated: Thu Nov 27 09:14:08 2008 (+0200)
//           By: Caner Candan
//     Update #: 1
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

#ifndef SQLITE_WRAPPER_H__
# define SQLITE_WRAPPER_H__

# include <string>
# include <vector>

# include <sqlite3.h>

class	SQLiteStatement
{
private:
  friend class SQLiteWrapper;
  SQLiteStatement(std::string const& statement, sqlite3* db);
public:
  SQLiteStatement();

  enum	dataType
    {
      INT = SQLITE_INTEGER,
      FLT = SQLITE_FLOAT  ,
      TXT = SQLITE_TEXT   ,
      BLB = SQLITE_BLOB   ,
      NUL = SQLITE_NULL   ,
    };

  dataType	DataType(int pos_zero_indexed);

  int		ValueInt(int pos_zero_indexed);
  std::string	ValueString(int pos_zero_indexed);

  //    SQLiteStatement(const SQLiteStatement&);
  ~SQLiteStatement();

  //SQLiteStatement& operator=(SQLiteStatement const&);

  bool	Bind(int pos_zero_indexed, std::string const& value);
  bool	Bind(int pos_zero_indexed, double value);
  bool	Bind(int pos_zero_indexed, int value);

  bool	BindNull(int pos_zero_indexed);

  bool	Execute();

  bool	NextRow();

  /*   Call Reset if not depending on the NextRow cleaning up.
       For example for select count(*) statements*/
  bool	Reset();

  bool	RestartSelect();

  void	End();

private:
  //void DecreaseRefCounter();

  //int* ref_counter_; // not yet used...
  sqlite3_stmt*	stmt_;
};

class	SQLiteWrapper
{
public:
  SQLiteWrapper();
  ~SQLiteWrapper();

  bool	Open(std::string const& db_file);

  class	ResultRecord
  {
  public:
    std::vector<std::string>	fields_;
  };

  class ResultTable
  {
    friend class SQLiteWrapper;
  public:
    ResultTable()
      : ptr_cur_record_(0)
    {}

    std::vector<ResultRecord> records_;

    ResultRecord*	next()
    {
      if (ptr_cur_record_ < records_.size()) {
	return &(records_[ptr_cur_record_++]);
      }

      return 0;
    }

  private:
    void	reset()
    {
      records_.clear();
      ptr_cur_record_=0;
    }
  private:
    unsigned int	ptr_cur_record_;
  };

  bool	SelectStmt(std::string const& stmt, ResultTable& res);
  bool	DirectStatement(std::string const& stmt);
  SQLiteStatement*	Statement(std::string const& stmt);

  std::string	LastError();

  // Transaction related
  bool Begin();
  bool Commit();
  bool Rollback();
private:
  static int	SelectCallback(void *p_data, int num_fields,
			       char **p_fields, char **p_col_names);

  sqlite3*	db_;
};

#endif // !SQLITE_WRAPPER_H

// 
// SQLiteWrapper.h ends here
