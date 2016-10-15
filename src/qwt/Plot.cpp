#include <iostream>
#include "Plot.h"
#include <qwt_plot_grid.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>
#include <qwt_plot_curve.h>

Plot::Plot(QWidget *parent) :
  QwtPlot(parent),
  d_curve(NULL)
{
  // attach curve
  d_curve = new QwtPlotCurve();
  QPen pen(Qt::red, 5);
  d_curve->setPen(pen);
  d_curve->attach(this);

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
  grid->setMajPen(QPen(Qt::gray, 0, Qt::DotLine));
  grid->setMinPen(QPen(Qt::gray, 0, Qt::DotLine));
  grid->attach(this);
}

void Plot::setSymbol(QwtSymbol *symbol)
{
  d_curve->setSymbol(symbol);

  if (symbol == NULL)
    {
      d_curve->setStyle(QwtPlotCurve::Dots);
    }
}

void Plot::setSamples(const QVector<QPointF> &samples)
{
  d_curve->setSamples(samples);
}