#include "ScatterWindow.h"
#include "Plot.h"

#include <qwt_plot_rescaler.h>
#include <qwt_scale_div.h>

#include <QKeyEvent>
#include <qmath.h>

#include <fstream>
#include <iostream>
#ifndef WIN32
#include <cmath>
#endif

ScatterWindow::ScatterWindow(QWidget *parent, Qt::WindowFlags flags) :
    QMainWindow(parent, flags),
    plot_(new Plot(this))
{
    plot_->replot();
    setCentralWidget(plot_);
}

void ScatterWindow::openFile(const QString &infile)
{
    infile_ = infile;
    readPoints();
}

void ScatterWindow::readPoints()
{
    // start reading input file
    std::ifstream inputstream;
    inputstream.open(infile_.toStdString().c_str());
    if (!inputstream.is_open())
    {
        std::cerr << "error - could not open file "
                  << infile_.toStdString() << "\n";
    }

    // read points from file
    float x, y;
    char dummy;
    int counter;
    QVector<QwtPoint3D> samples;
    while (inputstream >> counter >> dummy >> x >> dummy >> y)
    {
        samples.push_back(QwtPoint3D(x, y, counter));
    }
    setSamples(QwtPoint3DSeriesData(samples));
}

void ScatterWindow::initRescaler()
{
    rescaler_ = new QwtPlotRescaler(plot_->canvas());
    rescaler_->setReferenceAxis( QwtPlot::xBottom );
    rescaler_->setAspectRatio( QwtPlot::yLeft, 1.0 );

    for ( int axis = 0; axis < QwtPlot::axisCnt; axis++ )
        rescaler_->setIntervalHint( axis, QwtInterval( -10, 10 ) );

    QwtPlotRescaler::ExpandingDirection direction = QwtPlotRescaler::ExpandUp;
    rescaler_->setRescalePolicy( QwtPlotRescaler::Expanding );

    rescaler_->setEnabled(true);
    for ( int axis = 0; axis < QwtPlot::axisCnt; axis++ )
        rescaler_->setExpandingDirection( direction );

    rescaler_->rescale();
}

void ScatterWindow::setSamples(const QwtPoint3DSeriesData &samples)
{
    plot_->setSamples(samples);
}

void ScatterWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_F5:
    case Qt::Key_R:
    {
        readPoints();
        plot_->replot();
        rescaler_->rescale();
        break;
    }
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
        break;
    }
}

void ScatterWindow::setAxes(const QwtPoint3DSeriesData &samples)
{
    QRectF rect = samples.boundingRect();
    qreal x = rect.right();
    qreal y = rect.top();
    qreal d = 1.1 * std::max(std::fabs(x), std::fabs(y));

    plot_->setAxisScale(QwtPlot::xBottom, -d, d, 16);
    plot_->setAxisScale(QwtPlot::yLeft, -d, d, 16);

    plot_->replot();
}
