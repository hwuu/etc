// $Id: heap.h 5444 2012-03-11 11:41:41Z haowu $

#ifndef _ETC_HEAP_H_
#define _ETC_HEAP_H_

#include "../base.h"

template<class T, class Comp = less<T> >
class Heap
{
public:
  Heap(int M, int N);
  ~Heap();
  //
  void Push(const T& val, int cat);
  void Pop();
  void Remove(int cat); // not safe. use it wisely.
  void Top(T* p_val, int* p_cat) const;
  int  Size() const;
  bool Empty() const;
  //
protected:
  //
  void _Adjust(int pos_hole, T val_hole, int cat_hole);
  void _Update(int pos, T val, int cat);
  //
  Comp  comp_;
  //
  int  M_; // maximum # of elements in the heap vector.
  int  N_; // # of categories, i.e. cat == 0, 1, ..., N_ - 1.
  T*   V_; // V_[i]: the i-th element of the heap vector.
  int* C_; // C_[i]: the category-id of D_[i], we require that C_[i] != C_[j] if i != j.
  int* P_; // P_[cat]: the position of the element in the heap vector whose category-id is cat.
  //
  int  m_; // current # of elements in the heap vector.
};

//
//
// public
//
//

template<class T, class Comp>
Heap<T, Comp>::Heap(int M, int N)
{
  comp_ = Comp();
  //
  M_ = M;
  N_ = N;
  V_ = new T[M_];
  C_ = new int[M_];
  P_ = new int[N_];
  //
  m_ = 0;
}

template<class T, class Comp>
Heap<T, Comp>::~Heap()
{
  delete V_;
  delete C_;
  delete P_;
}

//

template<class T, class Comp>
void Heap<T, Comp>::Push(const T& val, int cat)
{
  if (m_ == M_) {
    return;
  }
  V_[m_] = val;
  C_[m_] = cat;
  P_[cat] = m_;
  m_++;
  if (m_ < 2) {
    return;
  }
  int pos_hole = m_ - 1;
  T   val_hole = V_[m_ - 1];
  int cat_hole = C_[m_ - 1];
  int pos_parent = (pos_hole - 1) / 2;
  while (pos_hole > 0 && comp_(V_[pos_parent], val_hole)) {
    _Update(pos_hole, V_[pos_parent], C_[pos_parent]);
    pos_hole = pos_parent;
    pos_parent = (pos_hole - 1) / 2;
  }
  _Update(pos_hole, val_hole, cat_hole);
}

//

template<class T, class Comp>
void Heap<T, Comp>::Pop()
{
  if (m_ == 0) {
    return;
  }
  Remove(C_[0]);
}

//

template<class T, class Comp>
void Heap<T, Comp>::Remove(int cat)
{
  _Adjust(P_[cat], V_[m_ - 1], C_[m_ - 1]);
  m_--;
}

//

template<class T, class Comp>
void Heap<T, Comp>::Top(T* p_val, int* p_cat) const
{
  if (m_ == 0) {
    return;
  }
  *p_val = V_[0];
  *p_cat = C_[0];
}

//

template<class T, class Comp>
int Heap<T, Comp>::Size() const
{
  return m_;
}

//

template<class T, class Comp>
bool Heap<T, Comp>::Empty() const
{
  return m_ == 0;
}

//
//
// protected
//
//

template<class T, class Comp>
void Heap<T, Comp>::_Adjust(int pos_hole, T val_hole, int cat_hole)
{
  int pos_child = 2 * pos_hole + 1;
  while (pos_child <= m_ - 1) {
    if(pos_child <= m_ - 2 && comp_(V_[pos_child], V_[pos_child + 1])) {
      pos_child++;
    }
    if (comp_(val_hole, V_[pos_child])) {
      _Update(pos_hole, V_[pos_child], C_[pos_child]);
      pos_hole = pos_child;
      pos_child = 2 * pos_child + 1;
    } else {
      break;
    }
  }
  _Update(pos_hole, val_hole, cat_hole);
}

template<class T, class Comp>
void Heap<T, Comp>::_Update(int pos, T val, int cat)
{
  V_[pos] = val;
  C_[pos] = cat;
  P_[cat] = pos;
}

#endif
