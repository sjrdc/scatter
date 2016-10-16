#include "MainWindow.h"
#include "Plot.h"

#include <fstream>
#include <iostream>

#include <qmath.h>

MainWindow::MainWindow(QString infile)
{
  d_plot = new Plot(this);
  d_plot->setTitle(infile);
  setCentralWidget(d_plot);

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
  int counter;
  QPolygonF samples;
  while (inputstream >> counter >> x >> y)
    {
      samples += QPointF(x, y);
    }
  setSamples(samples);
}

void MainWindow::setSamples(const QPolygonF &samples)
{
  d_plot->setSamples(samples);
}
