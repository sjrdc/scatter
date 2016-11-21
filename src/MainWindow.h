#pragma once

#include <QMainWindow>
#include <QImage>

class QLabel;
class ScatterWindow;
class QKeyEvent;
class PSFWindow;

class MainWindow : public QMainWindow
{
public:
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = Q_NULLPTR,
               Qt::WindowFlags flags = Qt::WindowFlags());

    void openFile(const QString &filename);

protected:
    void readPoints();
  void keyPressEvent(QKeyEvent *event);
  // QImage dataToImage(float *data, size_t size, int width, int height);

  QTabWidget *tabWidget_;
  ScatterWindow *scatterWindow_;
  PSFWindow *psfwindow_;
  QString infile_;
};
