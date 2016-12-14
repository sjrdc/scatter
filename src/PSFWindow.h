#pragma once

#include <QMainWindow>
#include <qwt_point_3d.h>
#include <complex>
class ImageDisplay;

class PSFWindow : public QMainWindow
{
    Q_OBJECT
public:
    PSFWindow(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());
    void openFile(const QString &infile);
    void setSamples(const QVector<QwtPoint3D> &samples);
    void keyPressEvent(QKeyEvent *event);

private:
    QSize estimateSize(const QVector<QwtPoint3D> &samples) const;
    void display(std::complex<float>* f, size_t rows, size_t cols);
    ImageDisplay *imagedisplay_;
};
