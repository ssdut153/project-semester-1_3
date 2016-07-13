#include "stdafx.h"
#include "trayicon.h"
#include "traymenu.h"
#include "commonelements.h"

TrayIcon::TrayIcon(QWidget *parent):
    QSystemTrayIcon(parent),
    trmn(new TrayMenu)
{
    this->setToolTip("聊天工具");
    this->setIcon(QIcon(":/images/icon"));

    this->setContextMenu(trmn);
    connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(on_trayIcon_clicked(QSystemTrayIcon::ActivationReason)));

}

TrayIcon::~TrayIcon()
{
    delete trmn;
}

void TrayIcon::on_trayIcon_clicked(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        CommonElements *ce = CommonElements::getInstance();
        if(ce->isLogin())
        {
            ce->getMainWindow()->show();
        }
        else
        {
            ce->getLoginWindow()->show();
        }
        break;
    }
}
