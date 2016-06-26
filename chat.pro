#-------------------------------------------------
#
# Project created by QtCreator 2016-06-26T09:53:17
#
#-------------------------------------------------

QT += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chat
TEMPLATE = app


SOURCES += main.cpp \
    common/message/base/message.cpp \
    common/message/base/upmessage.cpp \
    common/message/base/usernamemessage.cpp \
    common/message/loginout/loginmessage.cpp \
    common/message/loginout/logoutmessage.cpp \
    common/message/reg/regusermessage.cpp \
    common/message/friendlist/getfriendlistmessage.cpp \
    common/message/friendlist/friendlistmessage.cpp \
    common/cJSON.c \
    tray/trayicon.cpp \
    tray/traymenu.cpp \
    commonelements.cpp \
    helper.cpp \
    window/loginwindow.cpp \
    window/mainwindow.cpp \
    window/regwindow.cpp

HEADERS  += \
    common/message/base/message.h \
    common/message/base/upmessage.h \
    common/message/base/usernamemessage.h \
    common/message/loginout/loginmessage.h \
    common/message/loginout/logoutmessage.h \
    common/message/reg/regusermessage.h \
    common/message/friendlist/getfriendlistmessage.h \
    common/message/friendlist/friendlistmessage.h \
    tray/trayicon.h \
    tray/traymenu.h \
    common/cJSON.h \
    stdafx.h \
    commonelements.h \
    helper.h \
    window/loginwindow.h \
    window/mainwindow.h \
    window/regwindow.h

FORMS    +=

RESOURCES += \
    images.qrc
