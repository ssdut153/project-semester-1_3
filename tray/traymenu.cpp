#include "stdafx.h"
#include "traymenu.h"
#include "window/loginwindow.h"
#include "tray/trayicon.h"
#include "helper.h"
#include "common/message/loginout/logoutmessage.h"
#include "commonelements.h"

TrayMenu::TrayMenu(QWidget *parent):
    QMenu(parent),
    exitAction(new QAction(this))
{
    //    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::X11BypassWindowManagerHint);
    exitAction->setText("退出");
    this->addAction(exitAction);
    connect(exitAction,SIGNAL(triggered()),this,SLOT(on_exitAction_triggered()));
}

TrayMenu::~TrayMenu()
{
    delete exitAction;
}

void TrayMenu::on_exitAction_triggered()
{
    Helper *helper = Helper::getInstance();
    helper->quit();
}
