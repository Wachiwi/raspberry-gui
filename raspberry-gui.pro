#-------------------------------------------------
#
# Project created by QtCreator 2015-11-04T12:46:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET      =   raspberry-gui
TEMPLATE    =   app

SOURCES     +=  main.cpp\
                mainwindow.cpp \
                qcustomplot.cpp \
    livefileplotter.cpp

HEADERS     +=  mainwindow.h \
                qcustomplot.h \
    livefileplotter.h

FORMS       +=  mainwindow.ui
