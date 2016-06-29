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
    searchWindow(0)
{
    ui->setupUi(this);
    CommonElements *ce = CommonElements::getInstance();
    getFriendListMessage gflm(ce->username);
    Helper *helper = Helper::getInstance();
    helper->writeClient(gflm);
    ui->usernameLabel->setText(ce->username);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addFriendItem(QString user, int status)
{
    for(QMap<QString, int>::iterator it = friendlist.begin();it != friendlist.end(); it++)
    {
        if(it.key() == user)
        {
            return;
        }
    }
    QListWidgetItem *item = new QListWidgetItem;
    if(status == 0)
    {
        item->setText(user + "(离线)");
    }
    else if(status == 1)
    {
        item->setText(user + "(在线)");
    }
    this->items.push_back(item);
}

void MainWindow::loadFriendList(std::vector<QString> &users, std::vector<int> &onlineStatus)
{
    friendlist.clear();
    int size = users.size();
    for(int i = 0 ;i < size;i++)
    {
        friendlist.insert(users[i], onlineStatus[i]);
    }
    for(QMap<QString, int>::iterator it = friendlist.begin();it != friendlist.end(); it++)
    {
        QListWidgetItem *item = new QListWidgetItem;
        if(it.value() == 0)
        {
            item->setText(it.key() + "(离线)");
        }
        else if(it.value() == 1)
        {
            item->setText(it.key() + "(在线)");
        }
        this->items.push_back(item);
    }
    for(int i = 0;i < size;i++)
    {
        ui->friendListWidget->addItem(items[i]);
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
        ce->client->write(lm.getJsonString().toStdString().c_str());
        ce->client->waitForBytesWritten();
        ce->application->quit();
    }
}

void MainWindow::setFriendStatus(QString friendName, bool online)
{
    int size = items.size();
    for(int i = 0;i < size;i++)
    {
        QListWidgetItem *item = items[i];
        if(item->text().left(item->text().size() - 4) == friendName)
        {
            if(online)
            {
                item->setText(friendName + "(在线)");
            }
            else
            {
                item->setText(friendName + "(离线)");
            }
        }
    }
}

ChatWindow *MainWindow::findChatWindow(QString friendName)
{
    int size = this->items.size();
    for(int i = 0;i <size;i++)
    {
        QListWidgetItem *item = this->items[i];
        QString name = item->text();
        if(name.left(name.size() - 4) == friendName)
        {
            if(this->chatWindows.contains(item))
            {
                return chatWindows.find(item).value();
            }
            else
            {
                ChatWindow *cw = new ChatWindow(this->username, item, this);
                this->chatWindows.insert(item, cw);
                cw->show();
                return cw;
            }
        }
    }
    return 0;
}

void MainWindow::on_friendListWidget_doubleClicked(const QModelIndex &)
{
    QListWidgetItem *item = ui->friendListWidget->currentItem();
    QString friendName = item->text();
    ChatWindow *cw = 0;
    if(chatWindows.contains(item))
    {
        cw = chatWindows.find(item).value();
        cw->setFocus();
    }
    else
    {
        cw = new ChatWindow(this->username, item, this);
        this->chatWindows.insert(item, cw);
        cw->show();
    }
}

void MainWindow::on_pushButton_clicked()
{
    searchWindow = new SearchWindow(this);
    searchWindow->show();
}
