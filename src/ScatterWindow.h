#pragma once

#include <QMainWindow>

#include <qwt_series_data.h>
class Plot;
class QwtPlotRescaler;

class ScatterWindow: public QMainWindow
{
    Q_OBJECT

public:
    ScatterWindow(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());
    void openFile(const QString &infile);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    void initRescaler();
    void readPoints();
    void setSamples(const QwtPoint3DSeriesData &samples);
    void setAxes(const QwtPoint3DSeriesData &samples);

    QString infile_;
    QwtPlotRescaler *rescaler_;
    Plot *plot_;
};
