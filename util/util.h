// $Id: util.h 5444 2012-03-11 11:41:41Z haowu $

#ifndef _ETC_UTIL_H_
#define _ETC_UTIL_H_

#include "../base.h"
#include "heap.h"

class Util
{
public:
  static int counter0_;
  static int counter1_;
  static int counter2_;
  //
  // Integer operations
  //
  static int    Min(int a, int b);
  static int    Min(int a, int b, int c);
  static int    Min(int a, int b, int c, int d);
  static int    Max(int a, int b);
  static int    Max(int a, int b, int c);
  static int    Max(int a, int b, int c, int d);
  static string SepDigit(int n, int d);
  static string Dec2Bin(int n);
  static string Format(double x, int n);
  //
  // String operations
  //
  static void   Split(const string& s, const string& d, vector<string>* p_result);
  static string LTrim(const string& s);
  static string Trim(const string& s);
  static string ToLowerCase(const string& s);
  static string Truncate(const string& s, int len);
  static bool   IsWordChar(char c);
  static bool   IsBlankChar(char c);
  static const char* Tokenize(const char* in, char* out);
  //
  // Sequence Operations
  //
  static bool IsSubSeq(const vector<int>& seq1, const vector<int>& seq2);
  static int  SeqComp (const vector<int>& seq1, const vector<int>& seq2);
  static bool SeqPred (const vector<int>& seq1, const vector<int>& seq2);
  //
  static void Minus(const vector<int>& seq1, const vector<int>& seq2, vector<int>* p_result);
  //
  static void Union  (const vector<int>& seq1, const vector<int>& seq2, vector<int>* p_result);
  static void Union  (const vector<const vector<int>*>& zp_seq, vector<int>* p_result);
  static void Isect_H(const vector<int>& seq1, const vector<int>& seq2, vector<int>* p_result);
  static void Isect_H(const vector<const vector<int>*>& zp_seq, vector<int>* p_result);
  static void Isect_P(const vector<int>& seq1, const vector<int>& seq2, vector<int>* p_result);
  static void Isect_P(const vector<const vector<int>*>& zp_seq, vector<int>* p_result);
  //
  // Combinations
  //
  static int  CalcMaxCombID(int N);
  static int  CalcCombID(const vector<int>& comb);
  static void CalcComb(int cid, vector<int>* p_comb);
  //
  // Random numbers
  //
  static void Normalize(int n, vector<double>* vec);
  //
  static unsigned int _Rand();
  static unsigned int _Rand(unsigned int lb, unsigned int ub);
  //
  static void Shuffle(int n, vector<int>* pz_id);
  static void InitRolette(const vector<int>& P, vector<int>* p_S);
  static int  Roulette(const vector<int>& S);
  //
  // The 'minimum view cover' problem
  //
  static void MinimumViewCover(const vector<vector<int> >& U,
                               const vector<int>& L,
                               const vector<int>& v,
                               vector<int>* p_C);
  //
  // old
  //
  static void Union_Old(const vector<const vector<int>*>& zp_seq, vector<int>* p_result);
  static void Isect_H_Old(const vector<const vector<int>*>& zp_seq, vector<int>* p_result);
  //
protected:
  //
  static Flag _BinarySearch(int key, const vector<int>& seq, int lb, int ub, int* p_pos);
  static Flag _ProbeSearch(int key, const vector<int>& seq, int lb, int ub, int* p_pos);
  //
  static unsigned int _Rand(unsigned int n_bit);
};

#endif
