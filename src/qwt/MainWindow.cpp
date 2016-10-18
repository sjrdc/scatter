#include "MainWindow.h"
#include "Plot.h"

#include <qwt_plot_rescaler.h>

#include <qwt_scale_div.h>
#include <fstream>
#include <iostream>

#include <qmath.h>

MainWindow::MainWindow(QString infile)
{
    d_plot = new Plot(this);
    d_plot->replot();

    readPoints(infile);

    d_plot->setAxisScale(0, -100, 100, 20);
    initRescaler();
    setCentralWidget(d_plot);
}

void MainWindow::readPoints(QString infile)
{
    // start reading input file
    std::ifstream inputstream;
    inputstream.open(infile.toStdString().c_str());
    if (!inputstream.is_open())
    {
        std::cerr << "error - could not open file "
                  << infile.toStdString() << "\n";
    }

    // read points from file
    float x, y;
    char dummy;
    int counter;
    QPolygonF samples;
    while (inputstream >> counter >> dummy >> x >> dummy >> y)
    {
        samples += QPointF(x, y);
    }
    setSamples(samples);
}

void MainWindow::initRescaler()
{

    d_rescaler = new QwtPlotRescaler(d_plot->canvas());
    d_rescaler->setReferenceAxis( QwtPlot::xBottom );
    d_rescaler->setAspectRatio( QwtPlot::yLeft, 1.0 );

    for ( int axis = 0; axis < QwtPlot::axisCnt; axis++ )
        d_rescaler->setIntervalHint( axis, QwtInterval( -10, 10 ) );

    QwtPlotRescaler::ExpandingDirection direction = QwtPlotRescaler::ExpandUp;
    d_rescaler->setRescalePolicy( QwtPlotRescaler::Expanding );

    d_rescaler->setEnabled( true );
    for ( int axis = 0; axis < QwtPlot::axisCnt; axis++ )
        d_rescaler->setExpandingDirection( direction );

    d_rescaler->rescale();
}

void MainWindow::setSamples(const QPolygonF &samples)
{
    d_plot->setSamples(samples);
}
