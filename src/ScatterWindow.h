#pragma once

#include <QMainWindow>

#include <qwt_series_data.h>
class ScatterPlot;
class QwtPlotRescaler;

class ScatterWindow: public QMainWindow
{
    Q_OBJECT

public:
    ScatterWindow(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());
    void keyPressEvent(QKeyEvent *event);
    void setSamples(const QVector<QwtPoint3D> &samples);

protected:
    void initRescaler();

    QwtPlotRescaler *rescaler_;
    ScatterPlot *plot_;
};
