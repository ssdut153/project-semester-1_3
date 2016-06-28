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

std::string Helper::getfromJson(std::string textJson, const char *name)
{
    QString str = name;
    str = "\"" + str + "\":";
    if (textJson.find(str.toStdString().c_str()) >= textJson.length())
        return "false";
    cJSON *json , *json_head;
    // 解析数据包
    const char* text = textJson.c_str();
    try
    {
        json = cJSON_Parse(text);
        if (!json)
            return "false";
        else
        {
            // 解析head
            json_head = cJSON_GetObjectItem(json , name);
            std::string head = json_head->valuestring;
            cJSON_Delete(json);
            return head;
        }
    }
    catch(...)
    {
        return "false";
    }
}

void Helper::readClient()
{
    CommonElements *ce = CommonElements::getInstance();
    QString str = ce->client->readAll();
    if(status == "none")
    {
        QString head = this->getfromJson(str.toStdString(), "head").c_str();
        if(head == "loginFeedBack")
        {
            QString status = this->getfromJson(str.toStdString(), "status").c_str();
            if (status == "true")
            {
                ce->username = this->getfromJson(str.toStdString(), "username");
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
            QString status = this->getfromJson(str.toStdString(), "status").c_str();
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
            fbm.loadfromJson(str.toStdString());
            if(QString(fbm.stat.c_str()) == "sendfail")
            {
                ChatWindow *chatWindow = CommonElements::getInstance()->mainWindow->findChatWindow(fbm.user.c_str());
                chatWindow->sendFail();
            }
        }
        else if(head == "p2p")
        {
            p2pMessage pm;
            pm.loadfromJson(str.toStdString());
            ChatWindow *chatWindow = CommonElements::getInstance()->mainWindow->findChatWindow(pm.FromUserName.c_str());
            if(chatWindow != 0)
            {
                chatWindow->appendText(pm.CreateTime.c_str(), pm.Content.c_str());
            }
            //qDebug() << pm.FromUserName.c_str() << " " << pm.ToUserName.c_str() << " " << pm.CreateTime.c_str() << " " << pm.Content.c_str();
        }
        else
        {
            //qDebug()<<str;
        }

    }
    else if(status == "getfriendlist")
    {
        status = "none";
        friendListMessage flm;
        if(flm.loadfromJson(str.toStdString())){
            ce->mainWindow->loadFriendList(flm.user, flm.stat);
        }
    }
    else
    {

    }
}

void Helper::writeClient(Message &message)
{
    CommonElements::getInstance()->client->write(message.getJsonString().c_str());
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
