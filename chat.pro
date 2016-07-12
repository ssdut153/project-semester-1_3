#-------------------------------------------------
#
# Project created by QtCreator 2016-06-16T08:23:28
#
#-------------------------------------------------

QT += core gui
QT += network
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chat
TEMPLATE = app

SOURCES += main.cpp \
    window/loginwindow.cpp \
    window/mainwindow.cpp \
    window/regwindow.cpp \
    window/chatwindow.cpp \
    window/searchwindow.cpp \
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
    common/message/loginout/listmessage.cpp \
    common/message/reg/regusermessage.cpp \
    common/message/friendlist/getfriendlistmessage.cpp \
    common/message/friendlist/friendlistmessage.cpp \
    common/message/function/forcelogoutmessage.cpp \
    common/message/function/p2pmessage.cpp \
    common/message/function/imagemessage.cpp \
    common/message/searchuser/searchusermessage.cpp \
    common/message/addfriend/addfriendmessage.cpp \
    common/message/addfriend/ajfriendmessage.cpp \
    common/message/addfriend/requestfriendmessage.cpp \
    common/message/addfriend/newfriendmessage.cpp \
    messagebox/exitmessagebox.cpp \
    helper.cpp \
    groupbox/logingroupbox.cpp \
    groupbox/waitinggroupbox.cpp \
    database.cpp \
    button/closebutton.cpp \
    common/message/function/filemessage.cpp \
    messagebox/logoutmessagebox.cpp \
    messagebox/addfriendmessagebox.cpp \
    button/miniumbutton.cpp \
    common/message/loginout/getlistmessage.cpp

HEADERS  += stdafx.h \
    window/loginwindow.h \
    window/mainwindow.h \
    window/regwindow.h \
    window/chatwindow.h \
    window/searchwindow.h \
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
    common/message/loginout/listmessage.h \
    common/message/reg/regusermessage.h \
    common/message/friendlist/getfriendlistmessage.h \
    common/message/friendlist/friendlistmessage.h \
    common/message/function/p2pmessage.h \
    common/message/function/forcelogoutmessage.h \
    common/message/function/imagemessage.h \
    common/message/searchuser/searchusermessage.h \
    common/message/addfriend/addfriendmessage.h \
    common/message/addfriend/ajfriendmessage.h \
    common/message/addfriend/requestfriendmessage.h \
    common/message/addfriend/newfriendmessage.h \
    messagebox/exitmessagebox.h \
    helper.h \
    classes.h \
    groupbox/logingroupbox.h \
    groupbox/waitinggroupbox.h \
    database.h \
    button/closebutton.h \
    common/message/function/filemessage.h \
    messagebox/logoutmessagebox.h \
    messagebox/addfriendmessagebox.h \
    button/miniumbutton.h \
    common/message/loginout/getlistmessage.h

RESOURCES += \
    images.qrc

DISTFILES += \
    ico.rc

RC_FILE = \
     ico.rc
