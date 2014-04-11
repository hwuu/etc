// $Id: kmeans.h 5444 2012-03-11 11:41:41Z haowu $
#ifndef _ETC_GEO_KMEANS_H_
#define _ETC_GEO_KMEANS_H_

#include "geo.h"
//
#include <vector>

using namespace std;

struct Cluster
{
  Coordinate     centroid_;
  vector<Point*> zp_point_;
};

typedef double (*CalcDistFunc)(const Coordinate& c1, const Coordinate& c2);

void Kmeans(int k, const vector<Point>& z_point, CalcDistFunc CalcDist,
            vector<Cluster>* pz_cluster);

#endif
