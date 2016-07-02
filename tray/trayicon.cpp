#include "stdafx.h"
#include "trayicon.h"
#include "traymenu.h"

TrayIcon::TrayIcon(QWidget *parent):
    QSystemTrayIcon(parent)
{
    this->setToolTip("聊天工具");
    this->setIcon(QIcon(":/images/icon"));

    this->trmn = new TrayMenu;
    this->setContextMenu(trmn);
}

TrayIcon::~TrayIcon()
{
    delete trmn;
}
