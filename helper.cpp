#include "helper.h"
#include "commonelements.h"
#include "messages.h"
#include "database.h"
#include "messagebox/exitmessagebox.h"
#include "messagebox/logoutmessagebox.h"
#include "messagebox/addfriendmessagebox.h"

Helper::Helper():
    client(0)
{

}

Helper::~Helper()
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

QString Helper::getfromJson(QByteArray textJson, QString key)
{
    QJsonParseError jsonParseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(textJson, &jsonParseError);
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
    QByteArray str = ce->client->readAll();
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
        RegDialog *regDialog = ce->loginWindow->getLoginGroupBox()->getRegDialog();
        if(regDialog != 0)
        {
            if(status == "true")
            {
                loginMessage lm(regDialog->getUsername(), regDialog->getPassword());
                this->writeClient(lm);
            }
            else
            {
                this->disconnectServer();
                ce->client->disconnect();
                regDialog->getMessageLabel()->setText("注册失败");
                regDialog->getRegButton()->setEnabled(true);
            }
        }
    }
    else if(head == "friendList")
    {
        friendListMessage flm;
        if(flm.loadfromJson(str)){
            ce->mainWindow->loadFriendList(flm.users);
            getListMessage glm(ce->username);
            this->writeClient(glm);
        }
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
            Database *db = Database::getInstance(pm.ToUserName);
            db->addMessage(pm.FromUserName, 0, pm.CreateTime,pm.Content);
            QString str = QString("<span style=\"color:green;\">") + pm.FromUserName + "</span> <span style=\"color:cyan;\">" + pm.CreateTime + "</span>";
            chatWindow->getMessageEdit()->append(str);
            chatWindow->readContent(pm.Content);
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
        SearchDialog *sd = ce->mainWindow->getSearchDialog();
        if(sd != 0)
        {
            if(status == "true")
            {
                QString searchName = this->getfromJson(str, "username");
                sd->showSearchUser(searchName);
            }
            else
            {
                sd->showSearchUser("");
            }
        }
    }
    else if(head == "requestFriend")
    {
        requestFriendMessage rfm;
        rfm.loadfromJson(str);
        AddFriendMessageBox afmb(rfm.fromuser);
        if(afmb.exec() == QMessageBox::RejectRole)
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
        ce->mainWindow->addFriendItem(nfm.user, nfm.status);
    }
    else if(head == "forceLogout")
    {
        forceLogoutMessage flm;
        flm.loadfromJson(str);
        if(flm.user == ce->username)
        {
            ce->disconnectServer();
            ce->loginWindow = new LoginWindow;
            delete ce->mainWindow;
            ce->mainWindow = 0;
            ce->username = "";
            ce->login = false;
            ce->loginWindow->show();
            LogoutMessageBox logoutMessageBox(ce->loginWindow);
            logoutMessageBox.exec();
        }
    }
    else if(head == "image")
    {
        imageMessage pm;
        pm.loadfromJson(str);
        ChatWindow *chatWindow = ce->mainWindow->getChatWindow(pm.FromUserName);
        if(chatWindow != 0)
        {/*
            Database *db = Database::getInstance(pm.ToUserName);
            db->addMessage(pm.FromUserName, 0, pm.CreateTime,pm.Content);*/
            chatWindow->receivePic(pm);
        }
    }
    else if(head == "listmessage")
    {
        listMessage lm;
        if(lm.loadfromJson(str))
        {
            int size = lm.messageFromUsers.size();
            for(int i = 0; i < size; i++)
            {
                ChatWindow *chatWindow = ce->mainWindow->getChatWindow(lm.messageFromUsers[i]);
                if(chatWindow != 0)
                {
                    Database *db = Database::getInstance(lm.user);
                    db->addMessage(lm.messageFromUsers[i], 0, lm.createTime[i], lm.createTime[i]);
                    QString str = QString("<span style=\"color:green;\">") + lm.messageFromUsers[i] + "</span> <span style=\"color:cyan;\">" + lm.createTime[i] + "</span>";
                    chatWindow->getMessageEdit()->append(str);
                    chatWindow->readContent(lm.contents[i]);
                }
            }
            size = lm.requestUsers.size();
            for(int i = 0; i < size; i++)
            {
                QString requestName = lm.requestUsers[i];
                AddFriendMessageBox afmb(requestName);
                if(afmb.exec() == QMessageBox::RejectRole)
                {
                    ajFriendMessage afm(ce->username, requestName, "false");
                    this->writeClient(afm);
                }
                else
                {
                    ajFriendMessage afm(ce->username, requestName, "true");
                    this->writeClient(afm);
                }
            }
        }
    }
    else if(head == "file")
    {
        fileMessage fm;
        fm.loadfromJson(str);
        ChatWindow *chatWindow = ce->mainWindow->getChatWindow(fm.FromUserName);
        if(chatWindow != 0)
        {
            chatWindow->receiveFile(fm);
        }
    }
    else
    {

    }
}

void Helper::writeClient(Message &message)
{
    QTcpSocket *client = CommonElements::getInstance()->client;
    client->write(message.getJsonString());
    //    client->waitForBytesWritten();
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
            this->client->waitForBytesWritten();
        }
        if(this->client != 0)
        {
            ce->disconnectServer();
        }
        ce->trayIcon->hide();
        ce->application->quit();
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
