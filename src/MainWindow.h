#pragma once

#include <QMainWindow>

class QLabel;
class ScatterWindow;

class MainWindow : public QMainWindow
{
public:
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = Q_NULLPTR,
               Qt::WindowFlags flags = Qt::WindowFlags());

    void openFile(const QString &filename);

protected:
    QTabWidget *tabWidget_;
    ScatterWindow *scatterWindow_;
    QLabel *psf_;
};
