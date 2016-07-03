#include "helper.h"
#include "commonelements.h"
#include "common/message/function/p2pmessage.h"
#include "common/message/base/feedbackmessage.h"
#include "common/message/loginout/loginmessage.h"
#include "common/message/friendlist/friendlistmessage.h"
#include "common/message/addfriend/requestfriendmessage.h"
#include "common/message/addfriend/ajfriendmessage.h"
#include "common/message/addfriend/newfriendmessage.h"
#include "common/message/function/forcelogoutmessage.h"
#include "messagebox/exitmessagebox.h"
#include "common/message/loginout/logoutmessage.h"
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
                ce->loginWindow->loginFail();
            }
        }
        else if(head == "regFeedBack")
        {
            QString status = this->getfromJson(str, "status");
            RegWindow *regWindow = ce->loginWindow->getLoginGroupBox()->getRegWindow();
            if(regWindow != 0)
            {
                if(status == "true")
                {
                    loginMessage lm(regWindow->getUsername(), regWindow->getPassword());
                    this->writeClient(lm);
                }
                else
                {
                    this->disconnectServer();
                    ce->client->disconnect();
                    regWindow->getMessageLabel()->setText("注册失败");
                    regWindow->getRegButton()->setEnabled(true);
                }
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
                ChatWindow *chatWindow = ce->mainWindow->getChatWindow(fbm.user);
                if(chatWindow != 0)
                {
                    chatWindow->getMessageEdit()->append("发送失败");
                }
            }
        }
        else if(head == "p2p")
        {
            p2pMessage pm;
            pm.loadfromJson(str);
            ChatWindow *chatWindow = ce->mainWindow->getChatWindow(pm.FromUserName);
            if(chatWindow != 0)
            {
                chatWindow->getMessageEdit()->append(pm.FromUserName + pm.CreateTime);
                chatWindow->getMessageEdit()->append(pm.Content);
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
                SearchWindow *sw = ce->mainWindow->getSearchWindow();
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
            QMessageBox messageBox(QMessageBox::Information, "好友添加请求", rfm.fromuser + "请求添加您为好友", 0, 0);
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
        else if(head == "forceLogout")
        {
            forceLogoutMessage flm;
            flm.loadfromJson(str);
            if(flm.user == ce->username)
            {
                ce->disconnectServer();
                ce->loginWindow = new LoginWindow;
                QMessageBox messageBox(QMessageBox::Information, "提示", "您的帐号已在其他设备上登录", 0, 0);
                delete ce->mainWindow;
                ce->mainWindow = 0;
                ce->username = "";
                ce->login = false;
                ce->loginWindow->show();
                messageBox.exec();
            }
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
            ce->mainWindow->loadFriendList(flm.users);
        }
    }
    else
    {

    }
}

void Helper::writeClient(Message &message)
{
    qDebug()<<message.getJsonString();
    QTcpSocket *client = CommonElements::getInstance()->client;
    client->write(message.getJsonString().toStdString().c_str());
    client->waitForBytesWritten();
}

void Helper::quit()
{
    ExitMessageBox emb;
    if (emb.exec() == QMessageBox::AcceptRole)
    {
        CommonElements *ce = CommonElements::getInstance();
        Helper *helper = Helper::getInstance();
        if(ce->login)
        {
            logoutMessage lm(ce->username);
            helper->writeClient(lm);
        }
        ce->getTrayIcon()->hide();
        ce->getApplication()->quit();
    }
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
