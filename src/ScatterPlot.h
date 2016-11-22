#pragma once

#include <qwt_plot.h>
#include <qwt_plot_spectrocurve.h>

class QwtPlotCurve;
class QwtSymbol;
class QwtColorMap;

class ScatterPlot : public QwtPlot
{
  Q_OBJECT

public:
  ScatterPlot(QWidget *parent = NULL);

  void setSymbol(QwtSymbol *);
  void setSamples(const QwtPoint3DSeriesData &samples);
  void toggleColorMap();
  void increaseDotSize(int d);

protected:
  void adaptAxesToSamples();

  void initColorMaps();
  QwtPlotSpectroCurve *curve;
  QwtColorMap *colorMap;
  bool activeColorMap;
};
