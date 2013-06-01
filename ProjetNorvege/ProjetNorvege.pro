#-------------------------------------------------
#
# Project created by QtCreator 2013-04-06T18:27:13
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjetNorvege
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

win32:QMAKE_LFLAGS+=/INCREMENTAL:NO




SOURCES += main.cpp\
        mainwindow.cpp \
    abstractcameramanager.cpp \
    testcameramanager.cpp \
    abstractcamera.cpp \
    testcamera.cpp \
    emptycameramanager.cpp \
    cameraproperty.cpp \
    qvideowidget.cpp

HEADERS  += mainwindow.h \
    abstractcameramanager.h \
    testcameramanager.h \
    abstractcamera.h \
    testcamera.h \
    emptycameramanager.h \
    cameraproperty.h \
    qvideowidget.h

FORMS    += \
    mainwindow.ui

RESOURCES += \
    Ressources.qrc
