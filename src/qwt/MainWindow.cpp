#include "MainWindow.h"
#include "Plot.h"

#include <qmath.h>

MainWindow::MainWindow(QString title)
{
  d_plot = new Plot(this);
  d_plot->setTitle(title);
  setCentralWidget(d_plot);
}

void MainWindow::setSamples(const QPolygonF &samples)
{
  d_plot->setSamples(samples);
}
