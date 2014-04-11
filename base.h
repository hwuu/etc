// $Id: base.h 5444 2012-03-11 11:41:41Z haowu $

#ifndef _ETC_BASE_H_
#define _ETC_BASE_H_

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cassert>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
//
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <string>
//
#include <algorithm>
#include <functional>
//
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

//
//
//

typedef int Flag;
//
const Flag SUCCESS = 0;
const Flag FAILURE = -1;
//
const int MAX_STRING_LENGTH  = 512;
const int MAX_KEYWORD_LENGTH = 32;

#ifdef _WIN32
#ifdef _MSC_VER
#include <hash_set>
using namespace stdext;
typedef hash_set<int> HashSet;
#else
#include <tr1/unordered_map>
#include <tr1/unordered_set>
using namespace tr1;
typedef unordered_set<int> HashSet;
#endif
#endif


//
//
//

#endif
