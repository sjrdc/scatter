
#include "MainWindow.h"

#include <qapplication.h>
#include <iostream>
#include <fstream>

int main( int argc, char **argv )
{
  std::string infile;
  std::string outfile;

  if (argc > 1)
    infile = std::string(argv[1]);
  
  QApplication a( argc, argv );

  MainWindow w(QString::fromStdString(infile));
  w.resize(800, 800);
  
  // start reading input file
  std::ifstream inputstream;
  inputstream.open(infile.c_str());
  if (!inputstream.is_open())
    {
      std::cerr << "error - could not open file "
		<< infile << "\n";
    }

  // read points from file
  float x, y;
  int counter;
  QPolygonF samples;
  while (inputstream >> counter >> x >> y)
    {
      samples += QPointF( x, y );
    }
  w.setSamples(samples);
  w.show();

  return a.exec();
}
