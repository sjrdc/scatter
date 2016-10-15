#include "DataArray.h"
#include <iostream>
#include <limits>

void DataArray::getBounds(int &xmin, int &xmax, int &ymin, int &ymax)
{
  if (this->size() < 1) throw 0;
  
  // initialize 
  xmin = front().x;
  xmax = front().x;
  ymin = front().y;
  ymax = front().y;

  for (Point2D p : *this)
    {
      if (p.x > xmax) xmax = p.x;
      else if (p.x < xmin) xmin = p.x;

      if (p.y > ymax) ymax = p.y;
      else if (p.y < ymin) ymin = p.y;
    }
}
