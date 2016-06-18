#-------------------------------------------------
#
# Project created by QtCreator 2016-06-16T08:23:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chat
TEMPLATE = app


SOURCES += main.cpp \
        loginwindow.cpp \
    stdafx.cpp \
    mainwindow.cpp \
    ui.cpp \
    tray/traymenu.cpp \
    tray/trayaction.cpp

HEADERS  += loginwindow.h \
    stdafx.h \
    mainwindow.h \
    ui.h \
    tray/traymenu.h \
    tray/trayaction.h

FORMS    += loginwindow.ui \
    mainwindow.ui

RESOURCES += \
    images.qrc
