// $Id: table.h 5444 2012-03-11 11:41:41Z haowu $

#ifndef _ETC_TEXT_TABLE_H_
#define _ETC_TEXT_TABLE_H_

//#include "../base.h"
//
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Table
{
public:
  struct Row
  {
    Row()
    {
    }
    vector<string> z_value_;
  };
  //
  Table();
  Table(const string& csv_file);
  ~Table();
  //
  void Open(const string& csv_file);
  bool HasNext() const;
  void Next(Row* p_row);
  void Close();
  //int GetSizeInByte();
  //
  vector<string> z_column_name_;
  //vector<Row>    z_row_;
protected:
  //
  ifstream ifs_;
  bool has_next_;
  string next_line_;
  //int size_in_byte_;
  //
  //void Parse(const string& csv_file);
  void _ParseRow(const string& str, Row* p_row);
  void _ParseValue(string::const_iterator* p_iter, string* p_value);
};

#endif
