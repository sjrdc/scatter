#include "ScatterWindow.h"
#include "ScatterPlot.h"

#include <qwt_plot_rescaler.h>
#include <qwt_scale_div.h>

#include <QKeyEvent>
#include <qmath.h>

#include <iostream>
#ifndef WIN32
#include <cmath>
#endif

ScatterWindow::ScatterWindow(QWidget *parent, Qt::WindowFlags flags) :
  QMainWindow(parent, flags),
  plot_(new ScatterPlot(this))
{
  initRescaler();
  setCentralWidget(plot_);
}

void ScatterWindow::initRescaler()
{
    rescaler_ = new QwtPlotRescaler(plot_->canvas());
    rescaler_->setReferenceAxis(QwtPlot::xBottom);
    rescaler_->setAspectRatio(QwtPlot::yLeft, 1.0);

    for (int axis = 0; axis < QwtPlot::axisCnt; axis++)
        rescaler_->setIntervalHint(axis, QwtInterval(-10, 10));

    QwtPlotRescaler::ExpandingDirection direction = QwtPlotRescaler::ExpandUp;
    rescaler_->setRescalePolicy(QwtPlotRescaler::Expanding);

    rescaler_->setEnabled(true);
    for ( int axis = 0; axis < QwtPlot::axisCnt; axis++ )
        rescaler_->setExpandingDirection(direction);
}

void ScatterWindow::setSamples(const QVector<QwtPoint3D> &samples)
{
  plot_->setSamples(QwtPoint3DSeriesData(samples));
  rescaler_->rescale();
}

void ScatterWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_C:
    {
        plot_->toggleColorMap();
        plot_->replot();
        break;
    }
    case Qt::Key_Plus:
    {
        plot_->increaseDotSize(1);
        plot_->replot();
        break;
    }
    case Qt::Key_Minus:
    {
        plot_->increaseDotSize(-1);
        plot_->replot();
        break;
    }
    default:
      event->ignore();
        break;
    }
}

