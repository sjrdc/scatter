#include <iostream>
#include <qwt_color_map.h>

#include "ImageDisplay.h"

ImageDisplay::ImageDisplay()
{
  colourmap = new QwtLinearColorMap(Qt::black, Qt::white);
  datamatrix = new ImageRasterData;
  plotimg = new QwtPlotSpectrogram();
  plotimg->setRenderThreadCount(0); // use system specific thread count
  plotimg->setColorMap(colourmap);
  plotimg->setData(datamatrix);

  this->setMinimumSize(300, 300);
  plotimg->attach(this);

}

ImageDisplay::~ImageDisplay()
{
  //   delete datamatrix;
  //   delete colourmap;
  
  delete plotimg;
}


QSize ImageDisplay::minimumSizeHint()
{
  return QSize(300, 300);
}

QSize ImageDisplay::maximumSizeHint()
{
  return QSize(300, 300);
}

QSize ImageDisplay::sizeHint()
{
  return QSize(300, 300);
}

void ImageDisplay::updateDisplay(QVector<double> v, int xdim, int ydim,
				 float minpixval, float maxpixval)
{
  datamatrix->setInterval(Qt::XAxis, QwtInterval(0, xdim));
  datamatrix->setInterval(Qt::YAxis, QwtInterval(0, ydim));  
  datamatrix->setInterval(Qt::ZAxis, QwtInterval(minpixval, maxpixval));
  datamatrix->setValueMatrix(v, xdim);

  this->replot();
}


