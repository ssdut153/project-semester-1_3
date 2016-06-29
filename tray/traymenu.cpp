#include "stdafx.h"
#include "traymenu.h"
#include "window/loginwindow.h"
#include "tray/trayicon.h"
#include "messagebox/exitmessagebox.h"
#include "common/message/loginout/logoutmessage.h"
#include "commonelements.h"

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
    ExitMessageBox emb;
    if (emb.exec() == QMessageBox::AcceptRole)
    {
        CommonElements *ce = CommonElements::getInstance();
        if(ce->login)
        {
            logoutMessage lm(ce->username);
            ce->client->write(lm.getJsonString().toStdString().c_str());
        }
        ce->trayIcon->hide();
        std::exit(0);
    }
}
