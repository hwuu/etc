#pragma once

#include "../base.h"

class RawQuery
{
public:
  //
  RawQuery(const char* query_string);
  ~RawQuery();
  const char* Get(const string& key) const;
protected:
  static char* _DecodeURI(const char* str, int len, char* target);
  static int   _IsHex(char c);
  //
  map<string, const char*> params_;
  vector<string>           keys_;
  char*                    buff_;
  unsigned int             size_;
};
