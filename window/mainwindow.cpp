#include "stdafx.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "commonelements.h"
#include "message/logoutmessage.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    username(CommonElements::getInstance()->username)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox messageBox(QMessageBox::Warning, "警告", "您真的要退出吗?", 0, 0);
    messageBox.setWindowFlags(Qt::WindowStaysOnTopHint| (this->windowFlags() &~ (Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint)));
    messageBox.addButton("是", QMessageBox::AcceptRole);
    messageBox.addButton("否", QMessageBox::RejectRole);
    event->ignore();
    if(messageBox.exec() == QMessageBox::RejectRole)
    {
//        event->ignore();
    }
    else
    {
        logoutMessage lm(this->username);
        CommonElements *ce = CommonElements::getInstance();
        ce->trayIcon->hide();
        ce->client->write(lm.getJsonString().c_str());
        ce->client->waitForBytesWritten();
        ce->a->quit();
    }
}

//void MainWindow::paintEvent(QPaintEvent *event)
//{
//    QBitmap bmp(this->size());
//    bmp.fill();
//    QPainter p(&bmp);
//    p.setRenderHint(QPainter::Antialiasing);
//    int arcR = 10;
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
