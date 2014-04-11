// $Id: doc_index.cc 5444 2012-03-11 11:41:41Z haowu $

#include "doc_index.h"

#include <cmath>

using namespace std;

DocIndex::DocIndex()
{
}

void DocIndex::Build(const vector<string>& z_str, const Lexer& lexer)
{
  z_wstr_.clear();
  m_wstr_w_.clear();
  zz_d_.clear();
  //
  // build inverted index and forward index
  //
  for (int i = 0; i < (int)z_str.size(); i++) {
    zs_w_.push_back(set<int>());
    //const char* p = (z_str[i]).c_str();
    vector<string> z_wstr;
    lexer.Tokenize(z_str[i], &z_wstr);
    for (int j = 0; j < (int)z_wstr.size(); j++) {
      string wstr = z_wstr[j];
      int wid = 0;
      map<string, int>::iterator iter = m_wstr_w_.find(wstr);
      if (iter == m_wstr_w_.end()) {
        wid = z_wstr_.size();
        z_wstr_.push_back(wstr);
        m_wstr_w_.insert(pair<string, int>(wstr, wid));
        zz_d_.push_back(vector<int>());
      } else {
        wid = iter->second;
      }
      zz_d_[wid].push_back(i);
      zs_w_[i].insert(wid);
    }
  }
  //
  // calculate IDFs
  //
  for (int i = 0; i < (int)zz_d_.size(); i++) {
    int D  = z_str.size();
    int Di = zz_d_[i].size();
    double idf = log((double)D / (double)Di);
    z_idf_.push_back(idf);
  }
}
