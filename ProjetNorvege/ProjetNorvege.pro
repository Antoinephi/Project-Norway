#-------------------------------------------------
#
# Project created by QtCreator 2013-04-06T18:27:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjetNorvege
TEMPLATE = app




SOURCES += main.cpp\
        mainwindow.cpp \
    abstractcameramanager.cpp \
    testcameramanager.cpp \
    abstractcamera.cpp \
    testcamera.cpp \
    emptycameramanager.cpp

HEADERS  += mainwindow.h \
    abstractcameramanager.h \
    testcameramanager.h \
    abstractcamera.h \
    testcamera.h \
    emptycameramanager.h

FORMS    += \
    mainwindow.ui
