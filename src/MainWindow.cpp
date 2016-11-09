#include "MainWindow.h"
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

MainWindow::MainWindow(QString infile)
{
    plot = new Plot(this);
    plot->replot();

    infile_ = infile;
    readPoints();

    initRescaler();
    setCentralWidget(plot);
}

void MainWindow::readPoints()
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

void MainWindow::initRescaler()
{
    rescaler = new QwtPlotRescaler(plot->canvas());
    rescaler->setReferenceAxis( QwtPlot::xBottom );
    rescaler->setAspectRatio( QwtPlot::yLeft, 1.0 );

    for ( int axis = 0; axis < QwtPlot::axisCnt; axis++ )
        rescaler->setIntervalHint( axis, QwtInterval( -10, 10 ) );

    QwtPlotRescaler::ExpandingDirection direction = QwtPlotRescaler::ExpandUp;
    rescaler->setRescalePolicy( QwtPlotRescaler::Expanding );

    rescaler->setEnabled(true);
    for ( int axis = 0; axis < QwtPlot::axisCnt; axis++ )
        rescaler->setExpandingDirection( direction );

    rescaler->rescale();
}

void MainWindow::setSamples(const QwtPoint3DSeriesData &samples)
{
    plot->setSamples(samples);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_F5:
    case Qt::Key_R:
      {
        readPoints();
        plot->replot();
        rescaler->rescale();
        break;
      }
    case Qt::Key_C:
    {
        plot->toggleColorMap();
        plot->replot();
        break;
    }
    case Qt::Key_Plus:
    {
        plot->increaseDotSize(1);
        plot->replot();
        break;
    }
    case Qt::Key_Minus:
    {
        plot->increaseDotSize(-1);
        plot->replot();
        break;
    }
    default:
        break;
    }
}

void MainWindow::setAxes(const QwtPoint3DSeriesData &samples)
{
    QRectF rect = samples.boundingRect();
    qreal x = rect.right();
    qreal y = rect.top();
    qreal d = 1.1 * std::max(std::fabs(x), std::fabs(y));

    plot->setAxisScale(QwtPlot::xBottom, -d, d, 16);
    plot->setAxisScale(QwtPlot::yLeft, -d, d, 16);

    plot->replot();
}
