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
    window/regwindow.cpp \
    tray/traymenu.cpp \
    tray/trayicon.cpp \
    commonelements.cpp \
    common/message/base/message.cpp \
    common/message/base/upmessage.cpp \
    common/message/base/usernamemessage.cpp \
    common/message/base/feedbackmessage.cpp \
    common/message/base/uumessage.cpp \
    common/message/loginout/loginmessage.cpp \
    common/message/loginout/logoutmessage.cpp \
    common/message/reg/regusermessage.cpp \
    common/message/friendlist/getfriendlistmessage.cpp \
    common/message/friendlist/friendlistmessage.cpp \
    common/message/function/p2pmessage.cpp \
    common/message/searchuser/searchusermessage.cpp \
    common/message/addfriend/addfriendmessage.cpp \
    common/message/addfriend/ajfriendmessage.cpp \
    common/message/addfriend/requestfriendmessage.cpp \
    common/message/addfriend/newfriendmessage.cpp \
    messagebox/exitmessagebox.cpp \
    helper.cpp \
    window/chatwindow.cpp \
    window/searchwindow.cpp \
    common/message/function/forcelogoutmessage.cpp

HEADERS  += stdafx.h \
    window/loginwindow.h \
    window/mainwindow.h \
    window/regwindow.h \
    ui.h \
    tray/traymenu.h \
    tray/trayicon.h \
    commonelements.h \
    common/message/base/message.h \
    common/message/base/upmessage.h \
    common/message/base/usernamemessage.h \
    common/message/base/feedbackmessage.h \
    common/message/base/uumessage.h \
    common/message/loginout/loginmessage.h \
    common/message/loginout/logoutmessage.h \
    common/message/reg/regusermessage.h \
    common/message/friendlist/getfriendlistmessage.h \
    common/message/friendlist/friendlistmessage.h \
    common/message/function/p2pmessage.h \
    common/message/searchuser/searchusermessage.h \
    common/message/addfriend/addfriendmessage.h \
    common/message/addfriend/ajfriendmessage.h \
    common/message/addfriend/requestfriendmessage.h \
    common/message/addfriend/newfriendmessage.h \
    messagebox/exitmessagebox.h \
    helper.h \
    window/chatwindow.h \
    classes.h \
    window/searchwindow.h \
    common/message/function/forcelogoutmessage.h

FORMS    += window/loginwindow.ui \
    window/mainwindow.ui \
    window/regwindow.ui \
    window/chatwindow.ui \
    window/searchwindow.ui

RESOURCES += \
    images.qrc

DISTFILES += \
    ico.rc

RC_FILE = \
     ico.rc
