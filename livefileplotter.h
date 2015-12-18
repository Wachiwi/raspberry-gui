#ifndef LIVEFILEPLOTTER_H
#define LIVEFILEPLOTTER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QFile>
#include <QTextStream>

#include <iostream>

#include "qcustomplot.h"
#include "ui_mainwindow.h"

namespace Ui {
    class LiveFilePlotter;
}

class LiveFilePlotter : public QThread {
    Q_OBJECT

public:
    explicit LiveFilePlotter(QObject *parent = 0);
    ~LiveFilePlotter();

    void run();

public slots:
    void changeFile(QString, QCustomPlot*, QLabel*);

private:
    QString fname;
    QCustomPlot *plot;
    QLabel *label;
};

#endif // LIVEFILEPLOTTER_H
