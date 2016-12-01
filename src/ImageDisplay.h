#pragma once

#include <QtGui>
#include <vector>


#include <qwt_plot.h>
#include <qwt_plot_spectrogram.h>

#include "ImageRasterData.h"
#include "LogColormap.h"

class ImageDisplay : public QwtPlot 
{
  Q_OBJECT

public:
  ImageDisplay();
  virtual ~ImageDisplay();

  void updateDisplay(QVector<double> v, int xdim, int ydim, float minpixval, float maxpixval);
  void toggleColormap();

protected:
  virtual QSize minimumSizeHint();
  virtual QSize maximumSizeHint();  
  virtual QSize sizeHint();  

  SwitchableLogColorMap *colourmap;

  /// should be a spectrogram plot
  QwtPlotSpectrogram *plotimg;
  /// data for plotimg
  ImageRasterData *datamatrix;

private:
};

