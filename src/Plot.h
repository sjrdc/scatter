#pragma once

#include <qwt_plot.h>
#include <qwt_plot_spectrocurve.h>

class QwtPlotCurve;
class QwtSymbol;
class QwtColorMap;

class Plot : public QwtPlot
{
    Q_OBJECT

public:
    Plot( QWidget *parent = NULL );

  void setSymbol(QwtSymbol *);
  void setSamples(const QwtPoint3DSeriesData &samples);
    void toggleColorMap();

    void increaseDotSize(int d);

private:
    void initColorMaps();
  QwtPlotSpectroCurve *curve;
  QwtColorMap *colorMap;
  bool activeColorMap;
};
