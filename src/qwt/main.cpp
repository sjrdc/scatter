
#include <qapplication.h>
#include "mainwindow.h"
#include <iostream>
#include <fstream>

#include <CImg.h>
#include <tclap/CmdLine.h>

static double randomValue()
{
    // a number between [ 0.0, 1.0 ]
	return ( qrand() % 100000 ) / 100000.0;
}

int main( int argc, char **argv )
{
  std::string infile;
  std::string outfile;
  bool display;
  try
    {  
      TCLAP::CmdLine cmdline("scatter", ' ', "1.0");

      TCLAP::ValueArg<std::string> infileArg("i","infile",
					     "Input file containing coordinates",
					     true, "", "datafile.ext", cmdline);
      TCLAP::ValueArg<std::string> outfileArg("o","outfile",
					      "Output file",
					      true, "", "image.ext", cmdline);

      TCLAP::SwitchArg displayArg("d","display",
				  "Display the image", cmdline, false);

      // Parse the argv array.
      cmdline.parse( argc, argv );

      // Get the value parsed by each arg. 
      infile = infileArg.getValue();
      outfile = outfileArg.getValue();
      display = displayArg.getValue();
    }
  catch (TCLAP::ArgException &e)  // catch any exceptions
    {
      std::cerr << "error: " << e.error()
		<< " for arg " << e.argId() << std::endl;
    }
  
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
