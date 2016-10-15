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

  short gridx = 12;
  short gridy = 12;
  int nx = xmax - xmin + 1;
  int ny = ymax - ymin + 1;
  int n = std::max(nx*gridx, ny*gridy);
  
  CImg<unsigned char> img(n, n, 1, 1, 0);

  bool drawgrid = true;
  if (drawgrid)
    {
      CImg<int> gx(n, 1, 1, 1, 0);
      CImg<int> gy(n, 1, 1, 1, 0);
      for (int i = 0; i < n; ++ i)
	{
	  gx(i) = i*gridx;
	  gy(i) = i*gridy;
	}
      const unsigned char gc = 128;
      img.draw_grid(gx, gy, &gc, 0.8, 0xCCCCCCCC, 0xCCCCCCCC);
    }
  
  const unsigned char cc = 255;

  for (Point2D p : data)
    {
      int y = n - 1 - (p.y - ymin)*gridy;
      int x = (p.x - xmin)*gridx;
      img.draw_circle(x, y, float(gridx)/4, &cc, 1);
    }

  img.resize(1024, 1024, 1, 1, 3);
  img.save(outfile.c_str());

  return 0;
}
