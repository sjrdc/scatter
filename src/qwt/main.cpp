#include <qapplication.h>
#include "mainwindow.h"
#include <iostream>
static double randomValue()
{
    // a number between [ 0.0, 1.0 ]
	return ( qrand() % 100000 ) / 100000.0;
}

int main( int argc, char **argv )
{
  QApplication a( argc, argv );

  MainWindow w;
  w.resize(800, 600);
    
  QPolygonF samples;
  int numPoints = 10000;
  for ( int i = 0; i < numPoints; i++ )
    {
      const double x = randomValue() * 24.0 + 1.0;
      const double y = ::log( 10.0 * ( x - 1.0 ) + 1.0 ) 
	* ( randomValue() * 0.5 + 0.9 );

      samples += QPointF( x, y );
    }
  w.setSamples(samples);
  w.show();

  return a.exec();
}
