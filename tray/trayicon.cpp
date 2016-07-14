#include "stdafx.h"
#include "trayicon.h"
#include "traymenu.h"
#include "commonelements.h"

TrayIcon::TrayIcon(QWidget *parent):
    QSystemTrayIcon(parent),
    trmn(new TrayMenu)
{
    this->setToolTip("聊天工具");
    this->setIcon(QIcon(":/images/ico_64"));

    this->setContextMenu(trmn);
    connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(on_trayIcon_clicked(QSystemTrayIcon::ActivationReason)));

}

TrayIcon::~TrayIcon()
{
    delete trmn;
}

void TrayIcon::on_trayIcon_clicked(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::ActivationReason::Trigger || reason == QSystemTrayIcon::ActivationReason::Trigger)
    {
        CommonElements *ce = CommonElements::getInstance();
        if(ce->isLogin())
        {
            ce->getMainWindow()->show();
        }
        else
        {
            ce->getLoginWindow()->show();
        }
    }
}
