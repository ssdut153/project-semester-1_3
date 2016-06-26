/*****************************************************************************************
 *  Copyright(c) 2016 Huwenqiang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: trayicon
 *  简要描述:
 *
 *  创建日期: 2016-6-26
 *  作者: Hu Wenqiang
 *  说明:
 *
 *  修改日期: 2016-6-26
 *  作者: Hu Wenqiang
 *  说明:
 ****************************************************************************************/
#include "mainwindow.h"
#include "common/message/loginout/logoutmessage.h"
#include "commonelements.h"
#include "helper.h"
/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    usernameLabel(new QLabel(this))
{
    this->setMinimumSize(300, 800);
    this->setMaximumSize(300, 800);

    CommonElements *ce = CommonElements::getInstance();

    usernameLabel->setGeometry(40, 20, 190, 30);

    usernameLabel->setText(ce->username.c_str());

}
/**
 * @brief MainWindow::closeEvent
 * @param event
 */
void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();

    Helper *helper = Helper::getInstance();
    logoutMessage lm(this->usernameLabel->text().toStdString());
    CommonElements *ce = CommonElements::getInstance();

    QMessageBox messageBox(QMessageBox::Warning, "警告", "您真的要退出吗?", 0, 0);
    messageBox.setWindowFlags(Qt::WindowStaysOnTopHint | (messageBox.windowFlags() &~ (Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint)));
    messageBox.addButton("是", QMessageBox::AcceptRole);
    messageBox.addButton("否", QMessageBox::RejectRole);

    if(!(messageBox.exec() == QMessageBox::RejectRole))
    {
        helper->writeClient(lm);
        ce->client->waitForBytesWritten();
        ce->trayIcon->hide();
        ce->application->quit();
    }
}
/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{

}
