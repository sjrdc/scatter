#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_ 1

#include <qmainwindow.h>

class Plot;
class QwtPlotRescaler;

class MainWindow: public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QString title);


private:
    void initRescaler();
    void readPoints(QString infile);
    void setSamples( const QPolygonF& samples );

    QwtPlotRescaler *d_rescaler;
  Plot *d_plot;
};

#endif
