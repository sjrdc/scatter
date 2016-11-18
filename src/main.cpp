
#include "ScatterWindow.h"

#include <qapplication.h>
#include <iostream>

int main( int argc, char **argv )
{
  std::string infile;
  std::string outfile;

  if (argc > 1)
    infile = std::string(argv[1]);
  
  QApplication a(argc, argv);

  ScatterWindow w(QString::fromStdString(infile));
  w.resize(800, 800);
  
  w.show();

  return a.exec();
}
