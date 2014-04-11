// $Id: quadtree.h 5444 2012-03-11 11:41:41Z haowu $

#ifndef _ETC_GEO_QUADTREE_H_
#define _ETC_GEO_QUADTREE_H_

#include "geo.h"
//
#include <fstream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

//
//
//

struct QuadtreeNode
{
  QuadtreeNode()
      : depth_(0), p_parent_(NULL), pp_child_(NULL)
  {
  }
  //
  int id_;
  //
  int depth_;
  Rectangle br_; // bounding rectangle
  //
  QuadtreeNode* p_parent_;
  QuadtreeNode** pp_child_;
  //
  vector<Point*> zp_point_;
};

//
//
//

class QuadtreeNeighborIterator
{
public:
  //
  class Checker
  {
  public:
    virtual bool CheckNode(const QuadtreeNode& node) = 0;
    virtual bool CheckPoint(const Point& point) = 0;
  };
  //
  QuadtreeNeighborIterator(const Point& query, const QuadtreeNode& root);
  QuadtreeNeighborIterator(const Point& query, const QuadtreeNode& root,
      const Checker& checker);
  bool HasNext() const;
  void Next(Point** pp_point, double* p_dist);
  //
protected:
  //
  struct QueueEntry
  {
    QueueEntry()
    {
    }
    //
    QueueEntry(int type, void* ptr, double dist)
        : type_(type), ptr_(ptr), dist_(dist)
    {
    }
    //
    int type_; // type_ == 0: node; type_ == 1: point.
    void* ptr_; // ptr_ refers to a node or a point.
    double dist_;
    //
    bool operator > (const QueueEntry& qe) const
    {
      return this->dist_ > qe.dist_;
    }
    //
    bool operator < (const QueueEntry& qe) const
    {
      return this->dist_ < qe.dist_;
    }
  };
  //
  Point query_;
  priority_queue<QueueEntry, vector<QueueEntry>, greater<QueueEntry> > queue_;
  //
  Checker* p_checker_;
};

//
//
//

void Quadtree_Init(const Rectangle& br, QuadtreeNode** pp_root);
void Quadtree_Add(const Point& point, int m, int d, QuadtreeNode* p_root);
void Quadtree_AssignIDs(QuadtreeNode* p_root, vector<QuadtreeNode*>* pzp_node);
void Quadtree_Find(const Point& query, const QuadtreeNode& root,
    QuadtreeNode** pp_leaf_node);
void Quadtree_Destroy(QuadtreeNode* p_root);
void Quadtree_Output(const QuadtreeNode& root, const string& filename);
int Quadtree_GetNumPoints(const QuadtreeNode& root);
int Quadtree_GetNumNodes(const QuadtreeNode& root);
int Quadtree_GetNumLeafNodes(const QuadtreeNode& root);
int Quadtree_GetHeight(const QuadtreeNode& root);
int Quadtree_GetSizeInByte(const QuadtreeNode& root);

//
//
//

void _Quadtree_Add(const Point& point, int m, int d,
    QuadtreeNode* p_non_leaf_node);
void _Quadtree_Split(int m, int d, QuadtreeNode* p_leaf_node);
void _Quadtree_Output(const QuadtreeNode& root, int pos, int* p_id,
    ofstream& ofs);

//
//
//

#endif
