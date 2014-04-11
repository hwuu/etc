// $Id: lexer.cc 5444 2012-03-11 11:41:41Z haowu $

#include "lexer.h"

//
//
// public
//
//

Lexer::Lexer()
{
  //
}

//
//
//

Lexer::Lexer(const string& sw_file)
{
  ifstream ifs(sw_file.c_str());
  string line;
  while (getline(ifs, line)) {
    line = Util::Trim(line);
    if (line == "") {
      continue;
    }
    s_sw_.insert(line);
  }
  ifs.close();
}

//
//
//

void Lexer::Tokenize(const string& str, vector<string>* pz_word) const
{
  char buff[0x100];
  const char* p = str.c_str();
  while (*p) {
    p = _Tokenize(p, buff);
    string word = buff;
    int len = word.length();
    if (len <= MAX_KEYWORD_LENGTH &&
        s_sw_.find(word) == s_sw_.end()) {
      pz_word->push_back(word);
    }
  }
}

//
//
// protected
//
//

bool Lexer::_IsValidCharacter(char c) const
{
  return /* c == '-' || */ (c >= 0 && isalnum(c));
}

//
//
//

const char* Lexer::_Tokenize(const char* in, char* out) const
{
  while (*in && !_IsValidCharacter(*in))
    in++;
  while (_IsValidCharacter(*in)) {
    *out = tolower(*in);
    out++;
    in++;
  }
  *out = 0;
  while (*in && !_IsValidCharacter(*in))
    in++;
  return in;
}
