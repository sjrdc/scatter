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

protected:
  void keyPressEvent(QKeyEvent *event);

private:
    void initRescaler();
    void readPoints();
    void setSamples( const QPolygonF& samples );

    QString infile_;
    QwtPlotRescaler *rescaler;
    Plot *plot;
};

#endif
