
#include "MainWindow.h"

#include <qapplication.h>
#include <iostream>

int main( int argc, char **argv )
{
  QString infile;

  if (argc > 1)
    infile = QString(argv[1]);
  
  QApplication a(argc, argv);

  MainWindow w;
  w.openFile(infile);

  w.resize(800, 800);
  w.show();

  return a.exec();
}
