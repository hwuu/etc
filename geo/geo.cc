// $Id: geo.cc 5444 2012-03-11 11:41:41Z haowu $

/*
 * common.cc
 *
 *  Created on: Jul 1, 2011
 *      Author: Hao Wu
 */

#include "geo.h"
//
#include <cmath>
#include <algorithm>

using namespace std;

//
//
//

double Geo::CalcDist(const Point& point1, const Point& point2)
{
  double dx = point2.coord_.x_ - point1.coord_.x_;
  double dy = point2.coord_.y_ - point1.coord_.y_;
  return sqrt(pow(dx, 2) + pow(dy, 2));
}

//
//
//

double Geo::CalcMinDist(const Point& point, const Rectangle& rect)
{
  /*
   * This code is partially copied and modified from http://goo.gl/pPrHj
   */
  double x1 = rect.coord1_.x_;
  double y1 = rect.coord1_.y_;
  double x2 = rect.coord2_.x_;
  double y2 = rect.coord2_.y_;
  double x = point.coord_.x_;
  double y = point.coord_.y_;
  //
  double dx1 = x - x1;
  double dx2 = x - x2;
  double dy1 = y - y1;
  double dy2 = y - y2;
  //
  if (dx1 * dx2 < 0) { // x is between x1 and x2
    if (dy1 * dy2 < 0) { // (x,y) is inside the rectangle
      return 0;
    }
    return min(fabs(dy1), fabs(dy2));
  }
  if (dy1 * dy2 < 0) { // y is between y1 and y2
    // we don't have to test for being inside the rectangle, it's already tested.
    return min(fabs(dx1), fabs(dx2));
  }
  double dist_ll = CalcDist(Point(Coordinate(x1, y1)), point);
  double dist_ul = CalcDist(Point(Coordinate(x1, y2)), point);
  double dist_lr = CalcDist(Point(Coordinate(x2, y1)), point);
  double dist_ur = CalcDist(Point(Coordinate(x2, y2)), point);
  return min(min(dist_ll, dist_ul), min(dist_lr, dist_ur));
}

//
//
//

double Geo::CalcMaxDist(const Point& point, const Rectangle& rect)
{
  double x1 = rect.coord1_.x_;
  double y1 = rect.coord1_.y_;
  double x2 = rect.coord2_.x_;
  double y2 = rect.coord2_.y_;
  double x = point.coord_.x_;
  double y = point.coord_.y_;
  double dist_ll = CalcDist(Point(Coordinate(x1, y1)), point);
  double dist_ul = CalcDist(Point(Coordinate(x1, y2)), point);
  double dist_lr = CalcDist(Point(Coordinate(x2, y1)), point);
  double dist_ur = CalcDist(Point(Coordinate(x2, y2)), point);
  return max(max(dist_ll, dist_ul), max(dist_lr, dist_ur));
}

//
//
//

bool Geo::Contain(const Point& point, const Rectangle& rect)
{
  double x1 = rect.coord1_.x_;
  double y1 = rect.coord1_.y_;
  double x2 = rect.coord2_.x_;
  double y2 = rect.coord2_.y_;
  double x = point.coord_.x_;
  double y = point.coord_.y_;
  return x >= x1 && x < x2 && y >= y1 && y < y2;
}

//
//
//

bool Geo::Contain(const Rectangle& rect_small, const Rectangle& rect_large)
{
  double x11 = rect_small.coord1_.x_;
  double y11 = rect_small.coord1_.y_;
  double x12 = rect_small.coord2_.x_;
  double y12 = rect_small.coord2_.y_;
  //
  double x21 = rect_large.coord1_.x_;
  double y21 = rect_large.coord1_.y_;
  double x22 = rect_large.coord2_.x_;
  double y22 = rect_large.coord2_.y_;
  //
  bool b1 = x21 <= x11 && x12 <= x22;
  bool b2 = y21 <= y11 && y12 <= y22;
  return b1 && b2;
}

//
//
//

bool Geo::Overlap(const Rectangle& rect1, const Rectangle& rect2)
{
  double x11 = rect1.coord1_.x_;
  double y11 = rect1.coord1_.y_;
  double x12 = rect1.coord2_.x_;
  double y12 = rect1.coord2_.y_;
  //
  double x21 = rect2.coord1_.x_;
  double y21 = rect2.coord1_.y_;
  double x22 = rect2.coord2_.x_;
  double y22 = rect2.coord2_.y_;
  //
  bool b1 = x21 < x12 && x11 < x22;
  bool b2 = y21 < y12 && y11 < y22;
  return b1 && b2;
}

//
///
////
/////
////
///
//
//
///
////
/////
////
///
//
//
///
////
/////
////
///
//
//
///
////
/////
////
///
//
//
///
////
/////
////
///
//
//
///
////
/////
////
///
//
//
///
////
/////
////
///
//
