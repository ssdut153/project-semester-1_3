#include "stdafx.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "commonelements.h"
#include "common/message/loginout/logoutmessage.h"
#include "common/message/friendlist/getfriendlistmessage.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    username(CommonElements::getInstance()->username),
    qlwi(0)
{
    ui->setupUi(this);
    CommonElements *ce = CommonElements::getInstance();
    getFriendListMessage gflm(ce->username);
    Helper *helper = Helper::getInstance();
    helper->writeClient(gflm);
    ui->usernameLabel->setText(ce->username.c_str());
}

MainWindow::~MainWindow()
{
    delete qlwi;
    delete ui;
}

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
    qlwi = new QListWidgetItem[size];
    qlwi->setText("我的好友");
    for(int i = 0;i < size;i++)
    {
        (qlwi + i)->setText(friendlist[i].c_str());
        ui->friendListWidget->addItem(qlwi + i);
    }
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

void MainWindow::on_friendListWidget_doubleClicked(const QModelIndex &index)
{
    ChatWindow *cw = new ChatWindow(this->username, ui->friendListWidget->currentItem()->text().toStdString(), this);
    this->chatWindows.push_back(cw);
    cw->show();
}
