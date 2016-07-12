#include "stdafx.h"
#include "trayicon.h"
#include "traymenu.h"

TrayIcon::TrayIcon(QWidget *parent):
    QSystemTrayIcon(parent),
    trmn(new TrayMenu)
{
    this->setToolTip("聊天工具");
    this->setIcon(QIcon(":/images/icon"));

    this->setContextMenu(trmn);
}

TrayIcon::~TrayIcon()
{
    delete trmn;
}
