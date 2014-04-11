// $Id: table.cc 5444 2012-03-11 11:41:41Z haowu $

#include "table.h"
//
#include <fstream>
#include <sstream>

using namespace std;

Table::Table()
{
}

//
//
//

Table::Table(const string& csv_file)
{
  Open(csv_file);
}

//
//
//

Table::~Table()
{
  ifs_.close();
}

//
//
//

void Table::Open(const string& csv_file)
{
  ifs_.open(csv_file.c_str());
  string str = "";
  getline(ifs_, str);
  Row head_row;
  _ParseRow(str, &head_row);
  z_column_name_ = head_row.z_value_;
  //
  if (getline(ifs_, next_line_)) {
    has_next_ = true;
  } else {
    has_next_ = false;
  }
}

//
//
//

bool Table::HasNext() const
{
  return has_next_;
}

//
//
//

void Table::Next(Row* p_row)
{
  _ParseRow(next_line_, p_row);
  //
  while (getline(ifs_, next_line_)) {
    if (next_line_ == "") {
      continue;
    } else {
      has_next_ = true;
      return;
    }
  }
  has_next_ = false;
}

//
//
//

void Table::Close()
{
  ifs_.close();
}

/*
void Table::Parse(const string& csv_file)
{
  ifstream ifs(csv_file.c_str());
  string str = "";
  getline(ifs, str);
  Row head_row;
  ParseRow(str, &head_row);
  z_column_name_ = head_row.z_value_;
  while (getline(ifs, str)) {
    Row row;
    ParseRow(str, &row);
    if (row.z_value_.size() > 0) {
      z_row_.push_back(row);
    }
  }
  ifs.close();
}
*/

//
//
//
//
// protected
//
//
//
//

void Table::_ParseRow(const string& str, Row* p_row)
{
  string::const_iterator iter = str.begin();
  string value = "";
  while (iter != str.end() && *iter != '\r') {
    _ParseValue(&iter, &value);
    p_row->z_value_.push_back(value);
    if (iter != str.end() && *iter == ',') {
      iter++;
    }
  }
}

//
//
//

void Table::_ParseValue(string::const_iterator* p_iter, string* p_value)
{
  string::const_iterator& iter = *p_iter;
  stringstream ss;
  //
  // beginning mark
  //
  if (*iter != '\"') {
    *p_value = "";
    return;
  }
  iter++;
  //
  // content
  //
  while (*iter != '\"') {
    char c = '\0';
    if (*iter == '\\') {
      iter++;
      if (*iter == 'n') {
        c = '\n';
      } else if (*iter == 'r') {
        c = '\r';
      } else if (*iter == '\"') {
        c = '\"';
      } else if (*iter == '\\') {
        c = '\\';
      }
    } else {
      c = *iter;
    }
    ss << c;
    iter++;
  }
  //
  // skip the ending mark
  //
  iter++;
  //
  // output
  //
  *p_value = ss.str();
}
