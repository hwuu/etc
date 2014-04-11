// $Id: geo.h 5444 2012-03-11 11:41:41Z haowu $

/*
* common.h
*
*  Created on: Jun 30, 2011
*      Author: Hao Wu
*/

#ifndef _ETC_GEO_GEO_H_
#define _ETC_GEO_GEO_H_

//
//
//

struct Coordinate
{
  Coordinate()
  {
  }
  Coordinate(double x, double y)
    : x_(x), y_(y)
  {
  }
  Coordinate(const Coordinate& coord)
    : x_(coord.x_), y_(coord.y_)
  {
  }
  double x_;
  double y_;
};

//
//
//

struct Dimension
{
  Dimension()
  {
  }
  Dimension(double w, double h)
    : w_(w), h_(h)
  {
  }
  Dimension(const Dimension& dim)
    : w_(dim.w_), h_(dim.h_)
  {
  }
  double w_;
  double h_;
};

//
//
//

struct Point
{
  Point()
  {
  }
  Point(double x, double y)
    : coord_(Coordinate(x, y))
  {
  }
  Point(const Coordinate& coord)
    : coord_(coord)
  {
  }
  Point(const Point& p)
    : coord_(p.coord_)
  {
  }
  Coordinate coord_;
};

//
//
//

struct Rectangle
{
  Rectangle()
  {
  }
  Rectangle(double x1, double y1, double x2, double y2)
    : coord1_(Coordinate(x1, y1)), coord2_(Coordinate(x2, y2))
  {
  }
  Rectangle(const Coordinate& coord1, const Coordinate& coord2)
    : coord1_(coord1), coord2_(coord2)
  {
  }
  Rectangle(const Rectangle& rect)
    : coord1_(rect.coord1_), coord2_(rect.coord2_)
  {
  }
  Coordinate coord1_;
  Coordinate coord2_;
};

//
//
//

class Geo
{
public:
  static double CalcDist(const Point& point1, const Point& point2);
  static double CalcMinDist(const Point& point, const Rectangle& rect);
  static double CalcMaxDist(const Point& point, const Rectangle& rect);
  static bool Contain(const Point& point, const Rectangle& rect);
  static bool Contain(const Rectangle& rect_small, const Rectangle& rect_large);
  static bool Overlap(const Rectangle& rect1, const Rectangle& rect2);
};

//
//
//

#endif /* _ETC_GEO_COMMON_H_ */
