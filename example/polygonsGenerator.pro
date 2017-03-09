#-------------------------------------------------
#
# Project created by QtCreator 2017-01-05T21:48:20
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = polygonsGenerator
DESTDIR = ../example
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        $$PWD/../PolygonsGenerator/polygongenerator.cpp \
        $$PWD/../PolygonsGenerator/imagesgenerator.cpp

HEADERS  += mainwindow.h \
        $$PWD/../PolygonsGenerator/polygongenerator.h \
        $$PWD/../PolygonsGenerator/imagesgenerator.h

FORMS    += mainwindow.ui
