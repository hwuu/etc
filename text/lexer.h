// $Id: lexer.h 5444 2012-03-11 11:41:41Z haowu $

#ifndef _ETC_TEXT_LEXER_H_
#define _ETC_TEXT_LEXER_H_

#include "../base.h"
#include "../util/util.h"

class Lexer
{
public:
  Lexer();
  Lexer(const string& sw_file);
  void AddStopWord(const string& word);
  bool IsStopWord(const string& word);
  void Tokenize(const string& str, vector<string>* pz_word) const;
protected:
  set<string> s_sw_;
  //
  bool _IsValidCharacter(char c) const;
  const char* _Tokenize(const char* in, char* out) const;
};

#endif
