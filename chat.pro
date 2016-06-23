#-------------------------------------------------
#
# Project created by QtCreator 2016-06-16T08:23:28
#
#-------------------------------------------------

QT += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chat
TEMPLATE = app

SOURCES += main.cpp \
        window/loginwindow.cpp \
    stdafx.cpp \
    window/mainwindow.cpp \
    ui.cpp \
    tray/traymenu.cpp \
    tray/trayaction.cpp \
    tray/trayicon.cpp \
    commonelements.cpp \
    message/message.cpp \
    message/loginmessage.cpp \
    cJSON.c \
    messagebox/exitmessagebox.cpp

HEADERS  += window/loginwindow.h \
    stdafx.h \
    window/mainwindow.h \
    ui.h \
    tray/traymenu.h \
    tray/trayaction.h \
    tray/trayicon.h \
    commonelements.h \
    message/message.h \
    message/loginmessage.h \
    cJSON.h \
    messagebox/exitmessagebox.h

FORMS    += window/loginwindow.ui \
    window/mainwindow.ui

RESOURCES += \
    images.qrc

DISTFILES += \
    ico.rc

RC_FILE = \
     ico.rc
