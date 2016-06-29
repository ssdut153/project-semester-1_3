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
    ExitMessageBox emb;
    if (emb.exec() == QMessageBox::AcceptRole)
    {
        CommonElements *ce = CommonElements::getInstance();
        if(ce->login)
        {
            logoutMessage lm(ce->username);
            ce->client->write(lm.getJsonString().toLatin1());
        }
        ce->trayIcon->hide();
        std::exit(0);
    }
}

//void TrayMenu::paintEvent(QPaintEvent *event)
//{
//    QBitmap bmp(this->size());
//    bmp.fill();
//    QPainter p(&bmp);
//    p.setRenderHint(QPainter::Antialiasing);
//    int arcR = 5;
//    QRect rect = this->rect();
//    QPainterPath path;
//    path.moveTo(arcR, 0);
//    path.arcTo(0, 0, arcR * 2, arcR * 2, 90.0f, 90.0f);
//    path.lineTo(0, rect.height() - arcR * 2);
//    path.arcTo(0, rect.height() - arcR * 2, arcR * 2, arcR * 2, 180.0f, 90.0f);
//    path.lineTo(rect.width() - arcR, rect.height());
//    path.arcTo(rect.width() - arcR * 2, rect.height() - arcR * 2, arcR * 2, arcR * 2, -90.0f, 90.0f);
//    path.lineTo(rect.width(), arcR);
//    path.arcTo(rect.width() - arcR * 2, 0, arcR * 2, arcR * 2, 0.0f, 90.0f);
//    path.lineTo(arcR, 0);
//    p.drawPath(path);
//    p.fillPath(path, QBrush(Qt::red));
//    setMask(bmp);
//}
