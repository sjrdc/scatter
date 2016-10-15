#pragma once

#include <list>
#include "Point2D.h"

class DataArray : public std::list<Point2D>
{
public:
  void getBounds(int &xmin, int &xmax, int &ymin, int &ymax);
};
