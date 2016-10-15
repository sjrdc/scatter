#include <iostream>
#include "plot.h"
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>
#include <qwt_plot_curve.h>

Plot::Plot( QWidget *parent ):
    QwtPlot( parent ),
    d_curve( NULL )
{
    canvas()->setStyleSheet(
        "border: 2px solid Black;"
        "border-radius: 15px;"
        "background-color: qlineargradient( x1: 0, y1: 0, x2: 0, y2: 1,"
            "stop: 0 LemonChiffon, stop: 1 PaleGoldenrod );"
    );
    
    // attach curve
    d_curve = new QwtPlotCurve( "Scattered Points" );
    QPen pen(QColor("Purple"));
    pen.setWidth(5);
    d_curve->setPen(pen);

    d_curve->attach( this );

    setSymbol( NULL );

    // panning with the left mouse button
    (void )new QwtPlotPanner( canvas() );

    // zoom in/out with the wheel
    QwtPlotMagnifier *magnifier = new QwtPlotMagnifier( canvas() );
    magnifier->setMouseButton( Qt::NoButton );
}

void Plot::setSymbol( QwtSymbol *symbol )
{
    d_curve->setSymbol( symbol );

    if ( symbol == NULL )
    {
        d_curve->setStyle( QwtPlotCurve::Dots );
    }
}

void Plot::setSamples( const QVector<QPointF> &samples )
{
    // d_curve->setPaintAttribute( 
    //     QwtPlotCurve::ImageBuffer, samples.size() > 1000 );
    d_curve->setSamples( samples );
}
