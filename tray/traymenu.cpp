#include "stdafx.h"
#include "traymenu.h"
#include "window/loginwindow.h"
#include "tray/trayicon.h"
extern TrayIcon *tric;
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
    QMessageBox msgBox(QMessageBox::Warning, "警告", "您真的要退出吗?", 0, 0);
    msgBox.setWindowFlags(Qt::WindowStaysOnTopHint| (msgBox.windowFlags() &~ (Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint)));
    msgBox.addButton("是", QMessageBox::AcceptRole);
    msgBox.addButton("否", QMessageBox::RejectRole);
    if (msgBox.exec() == QMessageBox::AcceptRole)
    {
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
