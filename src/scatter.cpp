#include <iostream>
#include <fstream>

#include <CImg.h>
#include <tclap/CmdLine.h>

#include "DataArray.h"
#include "Point2D.h"

using namespace cimg_library;

int main(int argc, char** argv)
{
  // Wrap everything in a try block.  Do this every time, 
  // because exceptions will be thrown for problems.
  std::string infile;
  std::string outfile;
  bool display;
  try
    {  
      TCLAP::CmdLine cmdline("scatter", ' ', "0.1");

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


  // start reading input file
  std::ifstream inputstream;
  inputstream.open(infile.c_str());
  if (!inputstream.is_open())
    {
      std::cerr << "error - could not open file "
		<< infile << "\n";
    }

  // read points from file
  DataArray data;
  int x, y, counter;
  while (inputstream >> counter >> x >> y)
    {
      data.push_back(Point2D(x, y));
    }
  inputstream.close();

  int xmin = std::numeric_limits<int>::min();
  int xmax = std::numeric_limits<int>::max();
  int ymin = std::numeric_limits<int>::min();
  int ymax = std::numeric_limits<int>::max();

  data.getBounds(xmin, xmax, ymin, ymax);

  int nx = xmax - xmin + 1;
  int ny = ymax - ymin + 1;
  int n = std::max(nx, ny);
  
  CImg<unsigned char> img(n, n, 1, 1, 128);
  for (Point2D p : data)
    {
      int y = n - 1 - (p.y - ymin);
      int x = p.x - xmin;

      std::cout << x << " " << y << std::endl;
      img(x, y) = 255;
    }

  img.resize(512, 512);
  img.save(outfile.c_str());
  return 0;
}
