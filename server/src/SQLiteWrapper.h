//
// SQLiteWrapper.h for server in /home/candan_c/cu/rendu/qlik/server/src
// 
// Made by caner candan
// Login   <candan_c@epitech.net>
// 
// Started on  Sat Oct 25 21:42:36 2008 caner candan
// Last update Sat Oct 25 21:48:29 2008 caner candan
//

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
