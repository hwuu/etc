// $Id: doc_index.h 5444 2012-03-11 11:41:41Z haowu $

#ifndef _ETC_DOC_INDEX_H_
#define _ETC_DOC_INDEX_H_

#include "../base.h"
#include "../util/util.h"
#include "lexer.h"

struct DocIndex
{
  DocIndex();
  void Build(const vector<string>& z_str, const Lexer& lexer);
  //
  //set<string>                 sw_; // set of stop words
  vector<string>          z_wstr_;
  map<string, int>      m_wstr_w_;
  vector<vector<int> >      zz_d_; // inverted index
  vector<set<int> >         zs_w_; // forward index
  vector<double>           z_idf_; // idf's
};

#endif
