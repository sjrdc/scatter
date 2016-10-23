#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_ 1

#include <qmainwindow.h>
#include <qwt_series_data.h>
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
    void setSamples( const QwtPoint3DSeriesData &samples );
    void setAxes(const QwtPoint3DSeriesData &samples);

    QString infile_;
    QwtPlotRescaler *rescaler;
    Plot *plot;
};

#endif
