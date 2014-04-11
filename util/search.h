// $Id: search.h 5444 2012-03-11 11:41:41Z haowu $

#ifndef _ETC_SEARCH_H_
#define _ETC_SEARCH_H_

#include "../base.h"

/*
*
* binary_search
*
* INPUT  key:      the element to be found in [first,last)
*        first:    the iterator of the first element
*        last:     the iterator of the last element
* OUTPUT p_result: the pointer of the iterator of the matched element, or that of the
*                  first element which is larger than key in [first,last)
* RETURN SUCCESS:  if exact matching is found
*/

template<class T, class Iter, class Comp>
Flag BinarySearch(const T& key, const Iter& first, const Iter& last, Comp comp, Iter* p_result)
{
  Iter j1 = first;
  Iter j2 = last;
  while (j1 < j2) {
    Iter j = j1 + (j2 - j1) / 2;
    *p_result = j;
    if (comp(key, *j)) {
      if (j == j1)
        break;
      j2 = j;
    } else if (comp(*j, key)) {
      j1 = j + 1;
      (*p_result)++;
    } else {
      return SUCCESS;
    }
  }
  *p_result = j1;
  return FAILURE;
}

//
//
//

template<class T, class Iter>
Flag BinarySearch(const T& key, const Iter& first, const Iter& last, Iter* p_result)
{
  return BinarySearch(key, first, last, less<T>(), p_result);
}

/*
*
* probe_search // The usage is the same as binary_search
*
* INPUT  key:      the element to be found in [first,last)
*        first:    the iterator of the first element
*        last:     the iterator of the last element
* OUTPUT p_result: the pointer of the iterator of the matched element, or that of the
*                  first element which is larger than key in [first,last)
* RETURN SUCCESS:  if exact matching is found
*/

template<class T, class Iter, class Comp>
static Flag ProbeSearch(const T& key, const Iter& first, const Iter& last, Comp comp, Iter* p_result)
{
  Iter j1 = first;
  Iter j2 = last;
  int bias = 1;
  while (j1 < j2) {
    Iter j = j1 + bias;
    if (j >= j2) {
      j = j2 - 1;
    }
    if (comp(key, *j)) {
      return BinarySearch(key, j1, j + 1, comp, p_result);
    } else if (comp(*j, key)) {
      j1 = j + 1;
      bias *= 2;
    } else {
      *p_result = j;
      return SUCCESS;
    }
  }
  *p_result = j2;
  return FAILURE;
}

//
//
//

template<class T, class Iter>
Flag ProbeSearch(const T& key, const Iter first, const Iter last, Iter* p_result)
{
  return ProbeSearch(key, first, last, less<T>(), p_result);
}

//
//
//

#endif
