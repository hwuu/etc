// $Id: util.cc 5444 2012-03-11 11:41:41Z haowu $

#include "util.h"
#include "search.h"

//
//
//////////////////////////////////////////////////////////////////////////
//
// public
//
//////////////////////////////////////////////////////////////////////////
//
//

int Util::counter0_ = 0;
int Util::counter1_ = 0;
int Util::counter2_ = 0;

//
//
//
//
// min / max
//
//
//
//

int Util::Min(int a, int b)
{
  return a > b ? b : a;
}

//
//
//

int Util::Min(int a, int b, int c)
{
  return Min(Min(a, b), c);
}

//
//
//

int Util::Min(int a, int b, int c, int d)
{
  return Min(Min(a, b), Min(c, d));
}

//
//
//

int Util::Max(int a, int b)
{
  return a > b ? a : b;
}

//
//
//

int Util::Max(int a, int b, int c)
{
  return Max(Max(a, b), c);
}

//
//
//

int Util::Max(int a, int b, int c, int d)
{
  return Max(Max(a, b), Max(c, d));
}

//
//
//

string Util::SepDigit(int n, int d)
{
  char buff[20];
  sprintf(buff, "%d", n);
  string s = "";
  string tmp = string(buff);
  int c = 0;
  for (int i = static_cast<int>(tmp.size()) - 1; i >= 0; i--) {
    if (c == d) {
      s.push_back(',');
      c = 0;
    }
    s.push_back(tmp[i]);
    c++;
  }
  reverse(s.begin(), s.end());
  return s;
}

string Util::Dec2Bin(int n)
{
  string s = "";
  while (n != 0) {
    string b = (n % 2 == 0) ? "0" : "1";
    s = b + s;
    n /= 2;
  }
  return s;
}

string Util::Format(double x, int n)
{
  char buff[50];
  sprintf(buff, "%.*f", n, x);
  return string(buff);
}

//
//
//
//
// string manipulation
//
//
//
//

void Util::Split(const string& s, const string& d, vector<string>* p_result)
{
  p_result->clear();
  string t = s;
  while (true) {
    size_t cutAt = t.find_first_of(d);
    if (cutAt == string::npos) {
      break;
    }
    if (cutAt > 0) {
      p_result->push_back(t.substr(0, cutAt));
    }
    t = t.substr(cutAt + 1);
  }
  if (t.length() > 0) {
    p_result->push_back(t);
  }
}

//
//
//

string Util::LTrim(const string& s)
{
  if (s == "") {
    return "";
  }
  int i = 0;
  while (IsBlankChar(s[i])) {
    i++;
  }
  return s.substr(i, s.length() - i);
}

//
//
//

string Util::Trim(const string& s)
{
  if (s == "") {
    return "";
  }
  int i = 0;
  while (IsBlankChar(s[i])) {
    i++;
  }
  int j = s.length() - 1;
  while (IsBlankChar(s[j])) {
    j--;
  }
  return s.substr(i, j - i + 1);
}

//
//
//

string Util::ToLowerCase(const string& s)
{
  stringstream ss;
  for (int i = 0; i < static_cast<int>(s.length()); i++) {
    char c = tolower(s[i]);
    ss << c;
  }
  return ss.str();
}

//
//
//

string Util::Truncate(const string& s, int len)
{
  stringstream ss;
  int l = 0;
  while (l <= len && l <= static_cast<int>(s.length())) {
    ss << s[l];
    l++;
  }
  if (len < static_cast<int>(s.length())) {
    ss << "...";
  }
  return ss.str();
}

//
//
//

bool Util::IsWordChar(char c)
{
  // return c < 0 || c > 255 || c == '-' || isalnum(c);
  //return c < 0 || c > 255 || isalnum(c);
  return isalnum(c) == 1;
}

//
//
//

bool Util::IsBlankChar(char c)
{
  return (c == ' ' || c == '\t' || c == '\r');
}

//
//
//

const char* Util::Tokenize(const char* in, char* out)
{
  while (*in && !IsWordChar(*in))
    in++;
  while (IsWordChar(*in)) {
    *out = tolower(*in);
    out++;
    in++;
  }
  *out = 0;
  while(*in && !IsWordChar(*in))
    in++;
  return in;
}

//
//
//
//
// sequence operations
//
//
//
//

bool Util::IsSubSeq(const vector<int>& seq1, const vector<int>& seq2)
{
  int p = 0;
  for (int i = 0; i < static_cast<int>(seq1.size()); i++) {
    int v = seq1[i];
    int q = 0;
    Flag flag = _ProbeSearch(v, seq2, p, seq2.size() - 1, &q);
    p = q;
    if (flag != SUCCESS) {
      return false;
    }
  }
  return true;
}

//
//
//

int Util::SeqComp(const vector<int>& seq1, const vector<int>& seq2)
{
  int n1 = seq1.size();
  int n2 = seq2.size();
  int m = Util::Min(n1, n2);
  for (int i = 0; i < m; i++) {
    int a = seq1[i];
    int b = seq2[i];
    if (a < b) {
      return -1;
    } else if (a > b) {
      return 1;
    }
  }
  if (n1 < n2) {
    return -1;
  } else if (n1 > n2) {
    return 1;
  }
  return 0;
}

//
//
//

bool Util::SeqPred(const vector<int>& seq1, const vector<int>& seq2)
{
  return SeqComp(seq1, seq2) == -1;
}

//
//
//

void Util::Minus(const vector<int>& seq1, const vector<int>& seq2, vector<int>* p_result)
{
  int p = 0;
  for (int i = 0; i < static_cast<int>(seq1.size()); i++) {
    int v = seq1[i];
    int q = 0;
    Flag flag = _ProbeSearch(v, seq2, p, seq2.size() - 1, &q);
    p = q;
    if (flag != SUCCESS) {
      p_result->push_back(v);
    }
  }
}

//
//
//

void Util::Union(const vector<int>& seq1, const vector<int>& seq2, vector<int>* p_result)
{
  vector<const vector<int>*> zp_seq;
  zp_seq.push_back(&seq1);
  zp_seq.push_back(&seq2);
  Union(zp_seq, p_result);
}

//
//
//

void Util::Union(const vector<const vector<int>*>& zp_seq, vector<int>* p_result)
{
  int n = zp_seq.size();
  vector<int> J(n, 0);
  Heap<int, greater<int> > H(n, n);
  //
  for (int k = 0; k < n; k++) {
    const vector<int>& seq = *(zp_seq[k]);
    if (seq.size() > 0) {
      H.Push(seq[0], k);
    }
  }
  //
  while (!H.Empty()) {
    int t, k;
    H.Top(&t, &k);
    H.Pop();
    if (p_result->empty() || p_result->back() < t) {
      p_result->push_back(t);
    }
    int& pos = J[k];
    const vector<int>& seq = *(zp_seq[k]);
    if (pos < static_cast<int>(seq.size()) - 1) {
      pos++;
      H.Push(seq[pos], k);
    }
  }
}

//
//
//

void Util::Isect_H(const vector<int>& seq1, const vector<int>& seq2, vector<int>* p_result)
{
  vector<const vector<int>*> zp_seq;
  zp_seq.push_back(&seq1);
  zp_seq.push_back(&seq2);
  Isect_H(zp_seq, p_result);
}

//
//
//

void Util::Isect_H(const vector<const vector<int>*>& zp_seq, vector<int>* p_result)
{
  int n = static_cast<int>(zp_seq.size());
  vector<int> J(n, 0);
  Heap<int, greater<int> > H(n, n);
  for (int k = 0; k < n; k++) {
    int id = (*(zp_seq[k]))[J[k]];
    J[k]++;
    H.Push(id, k);
  }
  int top = 0;
  int count = 0;
  while (!H.Empty()) {
    int t, k;
    H.Top(&t, &k);
    if (count == 0) {
      top = t;
      count = 1;
    } else if (count > 0 && count < n) {
      if (top == t) {
        count++;
        if (count == n) {
          p_result->push_back(t);
          count = 0;
        }
      } else {
        top = t;
        count = 1;
      }
    }
    H.Pop();
    if (J[k] < static_cast<int>((*(zp_seq[k])).size())) {
      int id = (*(zp_seq[k]))[J[k]];
      J[k]++;
      H.Push(id, k);
    }
  }
}

//
//
//

void Util::Isect_P(const vector<int>& seq1, const vector<int>& seq2, vector<int>* p_result)
{
  vector<const vector<int>*> zp_seq;
  zp_seq.push_back(&seq1);
  zp_seq.push_back(&seq2);
  Isect_P(zp_seq, p_result);
}

//
//
//

void Util::Isect_P(const vector<const vector<int>*>& zp_seq, vector<int>* p_result)
{
  //
  // Note: we assume that zp_seq has already been sorted w.r.t. seq lengths.
  //
  const int N = zp_seq.size();
  vector<int> z_pos(N, 0);
  //
  const vector<int>& ss = *zp_seq[0];
  //
  for (int pos = 0; pos < static_cast<int>(ss.size()); pos++) {
    int v = ss[pos];
    bool is_result = true;
    for (int i = 1; i < N; i++) {
      int p = 0;
      Flag flag = _ProbeSearch(v, *zp_seq[i], z_pos[i], zp_seq[i]->size() - 1, &p);
      z_pos[i] = p;
      if (flag != SUCCESS) {
        is_result = false;
        break;
      }
    }
    if (is_result) {
      p_result->push_back(v);
    }
  }
}

//
//
//
//
// combinations
//
//
//
//

int Util::CalcMaxCombID(int N)
{
  return (1 << N) - 1;
}

//
//
//

int Util::CalcCombID(const vector<int>& comb)
{
  int cid = 0;
  for (int i = 0; i < static_cast<int>(comb.size()); i++) {
    cid += (1 << comb[i]);
  }
  return cid;
}

//
//
//

void Util::CalcComb(int cid, vector<int>* p_comb)
{
  int pos = 0;
  while (cid > 0) {
    if (cid % 2 == 1) {
      p_comb->push_back(pos);
    }
    cid /= 2;
    pos++;
  }
}

//
//
//

void Util::Normalize(int n, vector<double>* p_vec)
{
  double sum = 0;
  for (int i = 0; i < static_cast<int>(p_vec->size()); i++) {
    sum += pow((*p_vec)[i], (double)n);
  }
  for (int i = 0; i < static_cast<int>(p_vec->size()); i++) {
    (*p_vec)[i] /= sum;
  }
}

//
//
//
//
// random numbers
//
//
//
//

unsigned int Util::_Rand()
{
  return _Rand(sizeof(unsigned int) * 8);
}

//
//
//

unsigned int Util::_Rand(unsigned int lb, unsigned int ub)
{
  if (lb == 0 && ub + 1 == 0) {
    return _Rand(sizeof(unsigned int) * 8);
  }
  unsigned int L = ub - lb + 1;
  unsigned int n = 0;
  while (L >> n != 0) {
    n++;
  }
  while (true) {
    unsigned int x = _Rand(n);
    if (x < L) {
      return lb + x;
    }
  }
  return 0;
}

//
//
//

void Util::Shuffle(int n, vector<int>* pz_id)
{
  assert(n > 0 && pz_id != NULL);
  //
}

//
//
//

void Util::InitRolette(const vector<int>& P, vector<int>* p_S)
{
  assert(P.size() > 0);
  p_S->resize(P.size(), 0);
  (*p_S)[0] = P[0];
  for (int i = 1; i < static_cast<int>(P.size()); i++) {
    (*p_S)[i] = (*p_S)[i - 1] + P[i];
  }
}

//
//
//

int Util::Roulette(const vector<int>& S)
{
  assert(S.size() > 0);
  if (S.size() == 1) {
    return 0;
  }
  int max = S.back();
  int x = _Rand(0, max);
  vector<int>::const_iterator iter;
  ::BinarySearch(x, S.begin(), S.end(), &iter);
  return iter - S.begin();
}

//
//
//
//
// minimum view cover problem
//
//
//
//

void Util::MinimumViewCover(const vector<vector<int> >& U,
                            const vector<int>& L,
                            const vector<int>& v,
                            vector<int>* p_C)
{
  typedef pair<int, int> Score;
  //
  vector<int> D;
  for (int k = 0; k < static_cast<int>(U.size()); k++) {
    const vector<int>& u = U[k];
    if (u.size() > 0 && Util::IsSubSeq(u, v)) {
      D.push_back(k);
    }
  }
  //
  vector<int>& C = *p_C;
  vector<int> s;
  while (s != v) {
    Score max(0, 0);
    int imax = 0;
    for (int i = 0; i < static_cast<int>(D.size()); i++) {
      const vector<int>& u = U[D[i]];
      vector<int> delta;
      Util::Minus(u, s, &delta);
      if (delta.size() == 0) {
        continue;
      }
      Score score((int)delta.size(), -(int)L[D[i]]);
      //double score = log((double)delta.size()) / (double)L[D[i]];
      //double score = (double)delta.size() / (double)L[D[i]];
      if (max <= score) {
        max = score;
        imax = i;
      }
    }
    const vector<int>& u = U[D[imax]];
    C.push_back(D[imax]);
    D.erase(D.begin() + imax);
    vector<int> s_tmp;
    Util::Union(s, u, &s_tmp);
    s = s_tmp;
  }
}

//
//
// old
//
//

void Util::Union_Old(const vector<const vector<int>*>& zp_seq, vector<int>* p_result)
{
  typedef pair<int, int> HeapElem;
  priority_queue<HeapElem, vector<HeapElem>, greater<HeapElem> > H;
  //
  int n = zp_seq.size();
  vector<int> J(n, 0);
  //
  for (int k = 0; k < n; k++) {
    const vector<int>& seq = *(zp_seq[k]);
    if (seq.size() > 0) {
      H.push(make_pair(seq[0], k));
    }
  }
  //
  while (!H.empty()) {
    const HeapElem& e = H.top();
    int t = e.first;
    int k = e.second;
    H.pop();
    if (p_result->empty() || p_result->back() < t) {
      p_result->push_back(t);
    }
    int& pos = J[k];
    const vector<int>& seq = *(zp_seq[k]);
    if (pos < static_cast<int>(seq.size()) - 1) {
      pos++;
      H.push(make_pair(seq[pos], k));
    }
  }
}

void Util::Isect_H_Old(const vector<const vector<int>*>& zp_seq, vector<int>* p_result)
{
  typedef pair<int, int> HeapElem;
  priority_queue<HeapElem, vector<HeapElem>, greater<HeapElem> > H;
  //
  int n = zp_seq.size();
  vector<int> J(n, 0);
  //
  for (int k = 0; k < n; k++) {
    int id = (*(zp_seq[k]))[J[k]];
    J[k]++;
    H.push(make_pair(id, k));
  }
  //
  int min = 0;
  int count = 0;
  while (!H.empty()) {
    const HeapElem& e = H.top();
    int t = e.first;
    int k = e.second;
    if (count == 0) {
      min = t;
      count = 1;
    } else {
      if (min == t) {
        count++;
        if (count == n) {
          p_result->push_back(t);
          count = 0;
        }
      } else {
        if (count < n) {
          min = t;
          count = 1;
        }
      }
    }
    H.pop();
    if (J[k] < static_cast<int>((*(zp_seq[k])).size())) {
      int id = (*(zp_seq[k]))[J[k]];
      J[k]++;
      H.push(make_pair(id, k));
    } else {
      break;
    }
  }
}

//
//
//////////////////////////////////////////////////////////////////////////
//
// protected
//
//////////////////////////////////////////////////////////////////////////
//
//

/*
* INPUT  key:      the value to be found in seq
*        seq:      sequence of unsigned integers with a ascending order
*        lb:       lower-bound of the region in seq
*        ub:       upper-bound of the region in seq
* OUTPUT p_pos:    the position of the first occurrence of key, or that of the
*                  first value which is larger than key in seq[lb...ub]
* RETURN SUCCESS:  if exact matching is found
*/

Flag Util::_BinarySearch(int key, const vector<int>& seq, int lb, int ub, int* p_pos)
{
  if (seq.size() == 0) {
    return FAILURE;
  }
  Flag f;
  vector<int>::const_iterator iter;
  f = ::BinarySearch(key, seq.begin() + lb, seq.begin() + ub + 1, &iter);
  *p_pos = iter - seq.begin();
  return f;
}

/*
* The usage is the same as binary_search
*/

Flag Util::_ProbeSearch(int key, const vector<int>& seq, int lb, int ub, int* p_pos)
{
  if (seq.size() == 0) {
    return FAILURE;
  }
  Flag f;
  vector<int>::const_iterator iter;
  f = ::BinarySearch(key, seq.begin() + lb, seq.begin() + ub + 1, &iter);
  *p_pos = iter - seq.begin();
  return f;
}

//
//
//

unsigned int Util::_Rand(unsigned int n_bit)
{
  unsigned int x = 0;
  for (unsigned int i = 0; i < n_bit; i++) {
    x += (rand() % 2) << i;
  }
  return x;
}
