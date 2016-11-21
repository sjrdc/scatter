#pragma once

#include <QMainWindow>
#include <qwt_point_3d.h>
class ImageDisplay;

class PSFWindow : public QMainWindow
{
  Q_OBJECT
public:
    PSFWindow(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());
    void openFile(const QString &infile);
  void setSamples(const QVector<QwtPoint3D> &samples);
    void keyPressEvent(QKeyEvent *event);
  
protected:
  int estimateSize(const QVector<QwtPoint3D> &samples) const;

  ImageDisplay *imagedisplay_;
};
