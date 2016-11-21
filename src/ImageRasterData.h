#pragma once

#include <qwt_matrix_raster_data.h>

class ImageRasterData : public QwtMatrixRasterData
{
public:
  ImageRasterData() : QwtMatrixRasterData() {};
  virtual double value(double x, double y) const
  {
    return QwtMatrixRasterData::value(x, -y + numRows());
  }

};
