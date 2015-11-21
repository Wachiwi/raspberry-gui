#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>

#include "ui_mainwindow.h"
#include "livefileplotter.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

signals:
    void changeFile(QString fname, QCustomPlot *plot);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_visualizeButton_clicked();

private:
    Ui::MainWindow *ui;
    LiveFilePlotter *livePlotter;
};

#endif // MAINWINDOW_H
