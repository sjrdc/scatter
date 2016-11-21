#include "MainWindow.h"
#include "ScatterWindow.h"

#include <QLabel>

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) :
    QMainWindow(parent, flags),
    tabWidget_(new QTabWidget(this)),
    scatterWindow_(new ScatterWindow),
    psf_(new QLabel(this))
{
    tabWidget_->addTab(scatterWindow_, "scatterplot");
    tabWidget_->addTab(psf_, "PSF");

    setCentralWidget(tabWidget_);
}

void MainWindow::openFile(const QString &filename)
{
    scatterWindow_->openFile(filename);
}

