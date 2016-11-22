#include "MainWindow.h"
#include "PSFWindow.h"
#include "ScatterWindow.h"
#include "ImageDisplay.h"

#include <QLabel>
#include <QKeyEvent>

#include <fstream>
#include <iostream>
 
MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) :
    QMainWindow(parent, flags),
    tabWidget_(new QTabWidget(this)),
    scatterWindow_(new ScatterWindow),
    psfwindow_(new PSFWindow(this))
{
    tabWidget_->addTab(scatterWindow_, "scatterplot");
    tabWidget_->addTab(psfwindow_, "PSF");

    setCentralWidget(tabWidget_);
}

void MainWindow::openFile(const QString &filename)
{
  infile_ = filename;
  readPoints();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
  switch (event->key())
    {
    case Qt::Key_F5:
    case Qt::Key_R:
      readPoints();
      break;
    case Qt::Key_C:
    case Qt::Key_Plus:
    case Qt::Key_Minus:
      scatterWindow_->keyPressEvent(event);
      break;
    default:
      event->ignore();
      break;
    }
}

void MainWindow::readPoints()
{
    // start reading input file
    std::ifstream inputstream;
    inputstream.open(infile_.toStdString().c_str());
    if (!inputstream.is_open())
    {
        std::cerr << "error - could not open file "
                  << infile_.toStdString() << "\n";
    }

    // read points from file
    float x, y;
    char dummy;
    int counter;
    QVector<QwtPoint3D> samples;
    while (inputstream >> counter >> dummy >> x >> dummy >> y)
    {
        samples.push_back(QwtPoint3D(x, y, counter));
    }

    scatterWindow_->setSamples(samples);
    psfwindow_->setSamples(samples);
}
