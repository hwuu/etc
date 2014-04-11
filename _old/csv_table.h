// $Id: csv_table.h 5444 2012-03-11 11:41:41Z haowu $

#ifndef _ETC_CSV_TABLE_H_
#define _ETC_CSV_TABLE_H_

#include "../base.h"

class CsvTable
{
public:
  CsvTable(const string& csv_file);
  ~CsvTable();
  //
  void AddFile(const string& csv_file, bool skip_first_line = true);
  int  GetSizeInByte();
  void Clear();
  //
  vector<const char *>          z_attr_name_;
  vector<vector<const char *> > data_;
protected:
  vector<char *>                z_buff_;
};

#endif
