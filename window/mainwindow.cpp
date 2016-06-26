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
#include "common/message/friendlist/getfriendlistmessage.h"
#include "commonelements.h"
#include "helper.h"
#include "chatwindow.h"
/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    usernameLabel(new QLabel(this)),
    friendListWidget(new QListWidget(this)),
    qlwi(0)
{
    CommonElements *ce = CommonElements::getInstance();

    this->setMinimumSize(300, 600);
    this->setMaximumSize(300, 600);

    this->usernameLabel->setGeometry(40, 20, 190, 30);
    this->friendListWidget->setGeometry(30, 60, 240, 500);

    this->usernameLabel->setText(ce->username.c_str());

    Helper *helper = Helper::getInstance();
    getFriendListMessage gflm(ce->username);
    helper->writeClient(gflm);
    connect(friendListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(on_friendListWidget_doubleClicked(QListWidgetItem*)));
}
/**
 * @brief MainWindow::loadFriendList
 * @param users
 */
void MainWindow::loadFriendList(std::vector<std::string> &users)
{
    friendlist.clear();
    int size = users.size();
    for(int i = 0 ;i < size;i++)
    {
        friendlist.push_back(users[i]);
    }
    if(qlwi != 0)
    {
        delete qlwi;
    }
    qlwi = new QListWidgetItem[size + 1];
    qlwi->setText("我的好友");
    for(int i = 1;i < size + 1;i++)
    {
        (qlwi + i)->setText(friendlist[i].c_str());
        this->friendListWidget->addItem(qlwi + i);
    }
}
/**
 * @brief MainWindow::on_friendListWidget_doubleClicked
 * @param item
 */
void MainWindow::on_friendListWidget_doubleClicked(QListWidgetItem *item)
{
    ChatWindow *cw = new ChatWindow(this->usernameLabel->text().toStdString(), item->text().toStdString(), this);
    this->chatWindows.push_back(cw);
    cw->show();
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
