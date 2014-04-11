// $Id: kmeans.cc 5444 2012-03-11 11:41:41Z haowu $

#include "kmeans.h"
//
#include "geo.h"
#include "../util/util.h"
//
#include <limits>
#include <vector>

using namespace std;

void Kmeans(int k, const vector<Point>& z_point, CalcDistFunc CalcDist,
            vector<Cluster>* pz_cluster)
{
  assert(k > 0 && z_point.size() > 0);
  //
  // init1: calculate the diameter of the dataset (for convergence test)
  //
  double x_min = z_point[0].coord_.x_;
  double y_min = z_point[0].coord_.y_;
  double x_max = z_point[0].coord_.x_;
  double y_max = z_point[0].coord_.y_;
  for (int i = 0; i < (int)z_point.size(); i++) {
    const Point& point = z_point[i];
    double x = point.coord_.x_;
    double y = point.coord_.y_;
    if (x_min > x) {
      x_min = x;
    }
    if (y_min > y) {
      y_min = y;
    }
    if (x_max < x) {
      x_max = x;
    }
    if (y_max < y) {
      y_max = y;
    }
  }
  Coordinate ll = Coordinate(x_min, y_min);
  Coordinate ur = Coordinate(x_max, y_max);
  //double diameter = CalcDist(ll, ur);
  //
  // init2: randomly select k points as centroids
  //
  set<int> s_id;
  while (true) {
    srand((unsigned int)time(NULL));
    int id = Util::_Rand(0, z_point.size() - 1);
    if (s_id.count(id) == 0) {
      s_id.insert(id);
    }
    if ((int)s_id.size() >= k) {
      break;
    }
  }
  pz_cluster->clear();
  set<int>::iterator iter = s_id.begin();
  while (iter != s_id.end()) {
    const Point& point = z_point[(*iter)];
    Cluster c;
    c.centroid_.x_ = point.coord_.x_;
    c.centroid_.y_ = point.coord_.y_;
    pz_cluster->push_back(c);
    ++iter;
  }
  //
  // main loop
  //
  double err_old = -1;
  while (true) {
    //
    // assign data points to clusters
    //
    for (int i = 0; i < (int)pz_cluster->size(); i++) {
      Cluster& c = (*pz_cluster)[i];
      c.zp_point_.clear();
    }
    for (int i = 0; i < (int)z_point.size(); i++) {
      const Point& point = z_point[i];
      int j_nearest = -1;
      double dist_min = numeric_limits<double>::max();
      for (int j = 0; j < (int)pz_cluster->size(); j++) {
        Cluster& c = (*pz_cluster)[j];
        double dist = CalcDist(point.coord_, c.centroid_);
        if (dist < dist_min) {
          dist_min = dist;
          j_nearest = j;
        }
      }
      assert(j_nearest >= 0);
      Cluster& c_nearst = (*pz_cluster)[j_nearest];
      c_nearst.zp_point_.push_back((Point*)(&point));
    }
    //
    // update centroids
    //
    for (int i = 0; i < (int)pz_cluster->size(); i++) {
      Cluster& c = (*pz_cluster)[i];
      double sum_x = 0, sum_y = 0;
      int n = (int)c.zp_point_.size();
      for (int j = 0; j < n; j++) {
        Point& point = *(c.zp_point_[j]);
        sum_x += point.coord_.x_;
        sum_y += point.coord_.y_;
      }
      c.centroid_.x_ = sum_x / n;
      c.centroid_.y_ = sum_y / n;
    }
    //
    // test convergence
    //
    double thres = 0.99;
    double err = 0;
    for (int i = 0; i < (int)pz_cluster->size(); i++) {
      Cluster& c = (*pz_cluster)[i];
      for (int j = 0; j < (int)c.zp_point_.size(); j++) {
        Point& point = *(c.zp_point_[j]);
        err += CalcDist(point.coord_, c.centroid_);
      }
    }
    if (err_old != -1 && err / err_old > thres) {
      break;
    }
    err_old = err;
  } // while (true)
}
