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
    window/mainwindow.cpp \
    tray/traymenu.cpp \
    tray/trayaction.cpp \
    tray/trayicon.cpp \
    commonelements.cpp \
    message/base/message.cpp \
    message/base/usernamemessage.cpp \
    message/base/requestmessage.cpp \
    message/loginmessage.cpp \
    message/logoutmessage.cpp \
    message/regusermessage.cpp \
    message/getfriendlistmessage.cpp \
    cJSON.c \
    messagebox/exitmessagebox.cpp \
    window/regwindow.cpp \
    helper.cpp

HEADERS  += window/loginwindow.h \
    stdafx.h \
    window/mainwindow.h \
    ui.h \
    tray/traymenu.h \
    tray/trayaction.h \
    tray/trayicon.h \
    commonelements.h \
    message/base/message.h \
    message/base/usernamemessage.h \
    message/base/requestmessage.h \
    message/loginmessage.h \
    message/logoutmessage.h \
    message/regusermessage.h \
    message/getfriendlistmessage.h \
    cJSON.h \
    messagebox/exitmessagebox.h \
    window/regwindow.h \
    helper.h

FORMS    += window/loginwindow.ui \
    window/mainwindow.ui \
    window/regwindow.ui

RESOURCES += \
    images.qrc

DISTFILES += \
    ico.rc

RC_FILE = \
     ico.rc
