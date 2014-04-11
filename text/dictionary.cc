// $Id: dictionary.cc 5444 2012-03-11 11:41:41Z haowu $

/*
 * dictionary.cc
 *
 *  Created on: Jul 6, 2011
 *      Author: Hao Wu
 */

#include "dictionary.h"
//
#include <cassert>

using namespace std;

//
//
//

Dictionary::Dictionary()
{

}

//
//
//

void Dictionary::Clear()
{
  m_str_s_.clear();
  z_str_.clear();
}

//
//
//

int Dictionary::Add(const string& str)
{
  int s = -1;
  map<string, int>::iterator iter = m_str_s_.find(str);
  if (iter == m_str_s_.end()) {
    s = m_str_s_.size();
    m_str_s_.insert(make_pair(str, s));
    z_str_.push_back(str);
  } else {
    s = (*iter).second;
  }
  return s;
}

//
//
//

int Dictionary::GetStringId(const string& str) const
{
  int s = -1;
  map<string, int>::const_iterator iter = m_str_s_.find(str);
  if (iter != m_str_s_.end()) {
    s = (*iter).second;
  }
  return s;
}

//
//
//

const string& Dictionary::GetString(int s) const
{
  if (s >= 3) {
    int a = 0;
    a++;
  }
  assert(s < (int)z_str_.size());
  return z_str_[s];
}

//
//
//

int Dictionary::GetSize() const
{
  return (int)z_str_.size();
}

//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
