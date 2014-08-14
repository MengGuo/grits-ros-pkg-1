/*
 **************************************************************************
 * Class: Graham Scan Convex Hull                                         *
 * By Arash Partow - 2001                                                 *
 * URL: http://www.partow.net                                             *
 *                                                                        *
 * Copyright Notice:                                                      *
 * Free use of this library is permitted under the guidelines and         *
 * in accordance with the most current version of the Common Public       *
 * License.                                                               *
 * http://www.opensource.org/licenses/cpl.php                             *
 *                                                                        *
 **************************************************************************
*/


#ifndef INCLUDE_GRAHAMSCANCONVEXHULL_H
#define INCLUDE_GRAHAMSCANCONVEXHULL_H

#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <math.h>
#include "ConvexHull.h"


struct gs_PointVDG
{
public:
   gs_PointVDG(double _x = 0.0, double _y = 0.0, double _angle = 0.0) : x(_x), y(_y), angle(_angle){}
   double x;
   double y;
   double angle;
};

const double _180DivPI  = 57.295779513082320876798154814105000;
const int    counter_clock_wise = +1;
const int    clock_wise         = -1;


class GSPointVDGCompare
{
public:

   GSPointVDGCompare(gs_PointVDG* _anchor):anchor(_anchor){};

   bool operator()(const gs_PointVDG& p1, const gs_PointVDG& p2)
   {
      if (p1.angle < p2.angle)      return true;
      else if (p1.angle > p2.angle) return false;
      else if (is_equal(p1,p2))     return false;
      else if (lay_distance(anchor->x, anchor->y, p1.x, p1.y) < lay_distance(anchor->x, anchor->y, p2.x, p2.y))
         return true;
      else
         return false;
   }

private:

   inline bool is_equal(const gs_PointVDG p1, gs_PointVDG p2)
   {
      return  is_equal(p1.x,p2.x) && is_equal(p1.y,p2.y);
   }

   inline bool is_equal(const double v1, const double& v2, const double epsilon = 1.0e-12)
   {
      double diff = v1 - v2;
      return  (-epsilon <= diff) && (diff <= epsilon);
   }

   inline double lay_distance(const double& x1, const double& y1, const double& x2, const double& y2)
   {
      double dx = (x1 - x2);
      double dy = (y1 - y2);
      return (dx * dx + dy * dy);
   }

   gs_PointVDG* anchor;

};


class GrahamScanConvexHull : public ConvexHull
{
public:

   GrahamScanConvexHull(){};
  ~GrahamScanConvexHull(){};

   virtual bool operator()(const std::vector < PointVDG >& pnt, std::vector< PointVDG >& final_hull);

private:

   void graham_scan(std::vector< PointVDG >& final_hull);

   inline double cartesian_angle(double x, double y);

   inline int orientation(const gs_PointVDG& p1,
                          const gs_PointVDG& p2,
                          const gs_PointVDG& p3);

   inline int orientation(const double x1, const double y1,
                          const double x2, const double y2,
                          const double px, const double py);

   inline bool is_equal(const double v1, const double& v2, const double epsilon = 1.0e-12);

   std::vector<gs_PointVDG> point;
   gs_PointVDG              anchor;

};



#endif
