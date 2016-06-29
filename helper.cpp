#include "helper.h"
#include "commonelements.h"
#include "common/message/function/p2pmessage.h"
#include "common/message/base/feedbackmessage.h"
#include "common/message/loginout/loginmessage.h"
#include "common/message/friendlist/friendlistmessage.h"
#include <QDebug>

Helper::Helper():
    status("none"),
    client(0)
{

}

void Helper::connectServer()
{
    client = CommonElements::getInstance()->client;
    connect(client, SIGNAL(readyRead()), this, SLOT(readClient()));
}

void Helper::disconnectServer()
{
    disconnect(client, SIGNAL(readyRead()), this, SLOT(readClient()));
    client = 0;
}

QString Helper::getfromJson(QString textJson, QString key)
{
    QJsonParseError jsonParseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(textJson.toStdString().c_str(), &jsonParseError);
    if(jsonParseError.error == QJsonParseError::NoError)
    {
        if(jsonDocument.isObject())
        {
            QJsonObject jsonObject = jsonDocument.object();
            if(jsonObject.contains(key))
            {
                QJsonValue jsonValue = jsonObject.take(key);
                if(jsonValue.isString())
                {
                    return jsonValue.toString();
                }
            }
        }
    }
    return "";
}

void Helper::readClient()
{
    CommonElements *ce = CommonElements::getInstance();
    QString str = ce->client->readAll();
    if(status == "none")
    {
        QString head = this->getfromJson(str, "head");
        if(head == "loginFeedBack")
        {
            QString status = this->getfromJson(str, "status");
            if (status == "true")
            {
                ce->username = this->getfromJson(str, "username");
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
                ce->client->disconnect();
                ce->loginWindow->on_cancelButton_clicked();
                ce->loginWindow->clearPasswordEdit();
                ce->loginWindow->setMessageLabel("用户名或密码错误");
            }
        }
        else if(head == "regFeedBack")
        {
            QString status = this->getfromJson(str, "status");
            if(status == "true")
            {
                loginMessage lm(ce->loginWindow->regWindow->username,ce->loginWindow->regWindow->password);
                this->writeClient(lm);
            }
            else
            {
                this->disconnectServer();
                ce->client->disconnect();
                ce->loginWindow->regWindow->setMessageLabel("注册失败");
                ce->loginWindow->regWindow->setRegButtonEnabled(true);
            }
        }
        else if(head == "startSendList")
        {
            this->status = "getfriendlist";
        }
        else if(head == "defaultFeedBack")
        {
            feedBackMessage fbm;
            fbm.loadfromJson(str);
            if(fbm.stat == "sendfail")
            {
                ChatWindow *chatWindow = ce->mainWindow->findChatWindow(fbm.user);
                chatWindow->sendFail();
            }
        }
        else if(head == "p2p")
        {
            p2pMessage pm;
            pm.loadfromJson(str);
            ChatWindow *chatWindow = ce->mainWindow->findChatWindow(pm.FromUserName);
            qDebug()<<pm.Content;
            if(chatWindow != 0)
            {
                chatWindow->appendText(pm.CreateTime, pm.Content);
            }
        }
        else if(head == "online")
        {
            QString friendName = this->getfromJson(str, "username");
            ce->mainWindow->setFriendStatus(friendName, true);
        }
        else if(head == "offline")
        {
            QString friendName = this->getfromJson(str, "username");
            ce->mainWindow->setFriendStatus(friendName, false);
        }
        else
        {
            qDebug()<<str;
        }
    }
    else if(status == "getfriendlist")
    {
        status = "none";
        friendListMessage flm;
        if(flm.loadfromJson(str)){
            ce->mainWindow->loadFriendList(flm.user, flm.stat);
        }
    }
    else
    {

    }
}

void Helper::writeClient(Message &message)
{
    qDebug()<<message.getJsonString();
    CommonElements::getInstance()->client->write(message.getJsonString().toStdString().c_str());
}

Helper *Helper::helper = 0;

Helper *Helper::getInstance()
{
    if(helper == 0)
    {
        helper = new Helper;
    }
    return helper;
}
