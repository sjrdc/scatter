#include "Plot.h"

#include <qwt_color_map.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>
#include <qwt_plot_curve.h>

Plot::Plot(QWidget *parent) :
  QwtPlot(parent),
  curve(NULL)
{
  // attach curve
  curve = new QwtPlotSpectroCurve();
  curve->setPenWidth(5);
  curve->attach(this);

  initColorMaps();
  setStyleSheet("background: black; color: grey;");
  setSymbol(NULL);

  // panning with the left mouse button
  (void) new QwtPlotPanner(canvas());

  // zoom in/out with the wheel
  QwtPlotMagnifier *magnifier = new QwtPlotMagnifier(canvas());
  magnifier->setMouseButton(Qt::NoButton);

  // grid
  QwtPlotGrid *grid = new QwtPlotGrid;
  grid->enableXMin(true);
  grid->enableYMin(true);

  grid->setMajorPen(QPen(Qt::gray, 0, Qt::DotLine));
  grid->setMinorPen(QPen(Qt::gray, 0, Qt::DotLine));

  grid->attach(this);
}

void Plot::initColorMaps()
{
    activeColorMap = true;
    toggleColorMap();
}

void Plot::setSymbol(QwtSymbol *symbol)
{
  // curve->setSymbol(symbol);

  // if (symbol == NULL)
  //   {
  //     curve->setStyle(QwtPlotCurve::Dots);
  //   }
}

void Plot::setSamples(const QwtPoint3DSeriesData &samples)
{
  curve->setSamples(samples.samples());
}

void Plot::toggleColorMap()
{
    if (activeColorMap)
    {
        colorMap = new QwtLinearColorMap(Qt::red, Qt::red);
    }
    else {

        colorMap = new QwtHueColorMap();
    }
    curve->setColorMap(colorMap);

    activeColorMap = !activeColorMap;
}

void Plot::increaseDotSize(int d)
{
    curve->setPenWidth(curve->penWidth() + d);
}
