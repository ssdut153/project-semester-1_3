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

SOURCES += \
    main.cpp \
    window/loginwindow.cpp \
    window/mainwindow.cpp \
    window/chatwindow.cpp \
    dialog/searchdialog.cpp \
    dialog/expressiondialog.cpp \
    dialog/regdialog.cpp \
    tray/traymenu.cpp \
    tray/trayicon.cpp \
    button/closebutton.cpp \
    button/miniumbutton.cpp \
    groupbox/logingroupbox.cpp \
    groupbox/waitinggroupbox.cpp \
    common/message/base/message.cpp \
    common/message/base/upmessage.cpp \
    common/message/base/usernamemessage.cpp \
    common/message/base/feedbackmessage.cpp \
    common/message/base/uumessage.cpp \
    common/message/loginout/loginmessage.cpp \
    common/message/loginout/logoutmessage.cpp \
    common/message/loginout/listmessage.cpp \
    common/message/loginout/getlistmessage.cpp \
    common/message/reg/regusermessage.cpp \
    common/message/friendlist/getfriendlistmessage.cpp \
    common/message/friendlist/friendlistmessage.cpp \
    common/message/function/forcelogoutmessage.cpp \
    common/message/function/p2pmessage.cpp \
    common/message/function/imagemessage.cpp \
    common/message/function/filemessage.cpp \
    common/message/searchuser/searchusermessage.cpp \
    common/message/addfriend/addfriendmessage.cpp \
    common/message/addfriend/ajfriendmessage.cpp \
    common/message/addfriend/requestfriendmessage.cpp \
    common/message/addfriend/newfriendmessage.cpp \
    messagebox/exitmessagebox.cpp \
    messagebox/logoutmessagebox.cpp \
    messagebox/addfriendmessagebox.cpp \
    commonelements.cpp \
    helper.cpp \
    database.cpp

HEADERS  += \
    stdafx.h \
    window/loginwindow.h \
    window/mainwindow.h \
    window/chatwindow.h \
    dialog/searchdialog.h \
    dialog/expressiondialog.h \
    dialog/regdialog.h \
    tray/traymenu.h \
    tray/trayicon.h \
    button/closebutton.h \
    button/miniumbutton.h \
    groupbox/logingroupbox.h \
    groupbox/waitinggroupbox.h \
    common/message/base/message.h \
    common/message/base/upmessage.h \
    common/message/base/usernamemessage.h \
    common/message/base/feedbackmessage.h \
    common/message/base/uumessage.h \
    common/message/loginout/loginmessage.h \
    common/message/loginout/logoutmessage.h \
    common/message/loginout/listmessage.h \
    common/message/loginout/getlistmessage.h \
    common/message/reg/regusermessage.h \
    common/message/friendlist/getfriendlistmessage.h \
    common/message/friendlist/friendlistmessage.h \
    common/message/function/p2pmessage.h \
    common/message/function/forcelogoutmessage.h \
    common/message/function/imagemessage.h \
    common/message/function/filemessage.h \
    common/message/searchuser/searchusermessage.h \
    common/message/addfriend/addfriendmessage.h \
    common/message/addfriend/ajfriendmessage.h \
    common/message/addfriend/requestfriendmessage.h \
    common/message/addfriend/newfriendmessage.h \
    messagebox/exitmessagebox.h \
    messagebox/logoutmessagebox.h \
    messagebox/addfriendmessagebox.h \
    commonelements.h \
    helper.h \
    classes.h \
    database.h \
    messages.h

RESOURCES += \
    images.qrc

DISTFILES += \
    ico.rc

RC_FILE = \
     ico.rc
