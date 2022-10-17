#-------------------------------------------------
#
# Project created by QtCreator 2022-08-23T10:23:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

TARGET = ScreenDemo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        screen.cpp \
    serialportrx.cpp \
    tcpclient.cpp

HEADERS += \
        screen.h \
    data.h \
    qwidgetdraw.h \
    wave.h \
    mainwidget.h \
    serialportrx.h \
    tcpclient.h

FORMS += \
        screen.ui
