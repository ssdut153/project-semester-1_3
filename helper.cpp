/*****************************************************************************************
 *  Copyright(c) 2016 Huwenqiang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: trayicon
 *  简要描述:
 *
 *  创建日期: 2016-6-23
 *  作者: Hu Wenqiang
 *  说明:
 *
 *  修改日期: 2016-6-26
 *  作者: Hu Wenqiang
 *  说明:
 ****************************************************************************************/
#include "stdafx.h"
#include "helper.h"
#include "commonelements.h"
#include "common/message/loginout/loginmessage.h"
#include "common/message/friendlist/friendlistmessage.h"
#include "window/mainwindow.h"
#include "window/regwindow.h"
#include <QDebug>
/**
 * @brief Helper::Helper
 */
Helper::Helper():
    status("none"),
    client(0)
{

}
/**
 * @brief Helper::connectServer
 */
void Helper::connectServer()
{
    client = CommonElements::getInstance()->client;
    connect(client, SIGNAL(readyRead()), this, SLOT(readClient()));
}
/**
 * @brief Helper::disconnectServer
 */
void Helper::disconnectServer()
{
    disconnect(client, SIGNAL(readyRead()), this, SLOT(readClient()));
    client = 0;
}
/**
 * @brief Helper::readClient
 */
void Helper::readClient()
{
    CommonElements *ce = CommonElements::getInstance();
    QString str = client->readAll();
    QJsonParseError jsonError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(str.toLatin1(), &jsonError);
    if(jsonError.error == QJsonParseError::NoError)
    {
        if(status == "none" && jsonDocument.isObject())
        {
            QJsonObject jsonObject = jsonDocument.object();
            if(jsonObject.contains("head"))
            {
                QJsonValue headValue = jsonObject.take("head");
                if(headValue.isString())
                {
                    QString head = headValue.toString();
                    if(head == "loginFeedBack")
                    {
                        if(jsonObject.contains("status")){
                            QJsonValue statusValue = jsonObject.take("status");
                            if(statusValue.isString())
                            {
                                QString status= statusValue.toString();
                                if (status == "true")
                                {
                                    if(jsonObject.contains("username"))
                                    {
                                        QJsonValue usernameValue = jsonObject.take("username");
                                        if(usernameValue.isString())
                                        {
                                            ce->username = usernameValue.toString().toStdString();
                                        }
                                    }
                                    ce->login = true;
                                    ce->loginWindow->hide();
                                    delete ce->loginWindow;
                                    ce->loginWindow = 0;
                                    MainWindow *mw = new MainWindow;
                                    ce->mainWindow = mw;
                                    mw->show();
                                }
                                else
                                {
                                    this->disconnectServer();
                                    client->disconnect();
                                    ce->loginWindow->on_cancelButton_clicked();
                                    ce->loginWindow->passwordEdit->clear();
                                    ce->loginWindow->messageLabel->setText("用户名或密码错误");
                                }
                            }
                        }
                    }
                    else if(head == "regFeedBack")
                    {
                        if(jsonObject.contains("status"))
                        {
                            QJsonValue statusValue = jsonObject.take("status");
                            if(statusValue.isString())
                            {
                                QString status = statusValue.toString();
                                if(status == "true")
                                {
                                    loginMessage lm(ce->loginWindow->regWindow->username,ce->loginWindow->regWindow->password);
                                    this->writeClient(lm);
                                }
                                else
                                {
                                    this->disconnectServer();
                                    client->disconnect();
                                    ce->loginWindow->regWindow->messageLabel->setText("注册失败");
                                    ce->loginWindow->regWindow->regButton->setEnabled(true);
                                }
                            }
                        }
                    }
                    else if(head == "startSendList")
                    {
                        this->status = "getfriendlist";
                    }
                    else
                    {

                    }
                }
            }
        }
        else if(status == "getfriendlist" && jsonDocument.isArray())
        {
            qDebug()<<"friendlist";
            status = "none";
            friendListMessage flm;
            if(flm.loadfromJson(str.toStdString())){
                ce->mainWindow->loadFriendList(flm.user);
            }
        }
        else
        {

        }
    }
}
/**
 * @brief Helper::writeClient
 * @param message 需要发送的message类型消息
 */
void Helper::writeClient(Message &message)
{
    client->write(message.getJsonString().c_str());
}
/**
 * @brief Helper::quit
 */
void Helper::quit()
{
    QMessageBox messageBox(QMessageBox::Warning, "警告", "您真的要退出吗?", 0, 0);
    messageBox.setWindowFlags(Qt::WindowStaysOnTopHint | (messageBox.windowFlags() &~ (Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint)));
    messageBox.addButton("是", QMessageBox::AcceptRole);
    messageBox.addButton("否", QMessageBox::RejectRole);
    if(!(messageBox.exec() == QMessageBox::RejectRole))
    {
        CommonElements *ce = CommonElements::getInstance();
        ce->trayIcon->hide();
        ce->application->quit();
    }
}
/**
 * @brief Helper::helper
 */
Helper *Helper::helper = 0;
/**
 * @brief Helper::getInstance
 * @return Helper *
 */
Helper *Helper::getInstance()
{
    if(helper == 0)
    {
        helper = new Helper;
    }
    return helper;
}
