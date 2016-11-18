#pragma once

#include <QMainWindow>

#include <qwt_series_data.h>
class Plot;
class QwtPlotRescaler;

class ScatterWindow: public QMainWindow
{
  Q_OBJECT

public:
  ScatterWindow(QString title);

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
