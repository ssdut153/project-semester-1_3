#include "helper.h"
#include "commonelements.h"
#include "common/message/function/p2pmessage.h"
#include "common/message/base/feedbackmessage.h"
#include "common/message/loginout/loginmessage.h"
#include "common/message/friendlist/friendlistmessage.h"
#include "common/message/addfriend/requestfriendmessage.h"
#include "common/message/addfriend/ajfriendmessage.h"
#include "common/message/addfriend/newfriendmessage.h"
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
    qDebug()<<str;
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
        else if(head == "userInfo")
        {
            QString status = this->getfromJson(str, "status");
            if(status == "true")
            {
                QString searchName = this->getfromJson(str, "username");
                SearchWindow *sw = ce->mainWindow->searchWindow;
                if(sw != 0)
                {
                    sw->showSearchUser(searchName);
                }
            }
        }
        else if(head == "requestFriend")
        {
            requestFriendMessage rfm;
            rfm.loadfromJson(str);
            QMessageBox messageBox(QMessageBox::Warning, "好友添加请求", rfm.fromuser + "请求添加您为好友", 0, 0);
            messageBox.setWindowFlags(Qt::WindowStaysOnTopHint | (messageBox.windowFlags() &~ (Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint)));
            messageBox.addButton("同意", QMessageBox::AcceptRole);
            messageBox.addButton("拒绝", QMessageBox::RejectRole);
            if(messageBox.exec() == QMessageBox::RejectRole)
            {
                ajFriendMessage afm(ce->username, rfm.fromuser, "false");
                this->writeClient(afm);
            }
            else
            {
                ajFriendMessage afm(ce->username, rfm.fromuser, "true");
                this->writeClient(afm);
            }
        }
        else if(head == "newFriend")
        {
            newFriendMessage nfm;
            nfm.loadfromJson(str);
            ce->mainWindow->addFriendItem(nfm.user, 1);
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
