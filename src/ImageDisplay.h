#pragma once

#include <QtGui>
#include <vector>

#include <qwt_color_map.h>
#include <qwt_plot.h>
#include <qwt_plot_spectrogram.h>

#include "ImageRasterData.h"


class ImageDisplay : public QwtPlot 
{
  Q_OBJECT

public:
  ImageDisplay();
  virtual ~ImageDisplay();

  void updateDisplay(QVector<double> v, int xdim, int ydim, float minpixval, float maxpixval);
  
protected:
  virtual QSize minimumSizeHint();
  virtual QSize maximumSizeHint();  
  virtual QSize sizeHint();  

  /// the colourmap used to display images
  QwtLinearColorMap *colourmap;
  /// width of image
  int imagewidth;
  /// height of image
  int imageheight;
  /// minimum image pixel value
  float minpixval;
  /// maximum image pixel value
  float maxpixval;

  /// should be a spectrogram plot
  QwtPlotSpectrogram *plotimg;
  /// data for plotimg
  ImageRasterData *datamatrix;
			 


private:
};

