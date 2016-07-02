#include "stdafx.h"
#include "traymenu.h"
#include "helper.h"
#include "tray/trayicon.h"

TrayMenu::TrayMenu(QWidget *parent):
    QMenu(parent),
    exitAction(new QAction(this))
{
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
