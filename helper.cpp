#include "helper.h"
#include "commonelements.h"
#include "common/message/loginout/loginmessage.h"
#include "common/message/friendlist/friendlistmessage.h"
#include "window/mainwindow.h"
#include "window/regwindow.h"

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
                ce->loginWindow->passwordEdit->clear();
                ce->loginWindow->messageLabel->setText("用户名或密码错误");
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
                ce->loginWindow->regWindow->messageLabel->setText("注册失败");
                ce->loginWindow->regWindow->regButton->setEnabled(true);
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
    else if(status == "getfriendlist")
    {
        status = "none";
        friendListMessage flm;
        if(flm.loadfromJson(str.toStdString())){
            //            ce->mainWindow->loadFriendList(flm.user);
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

Helper *Helper::helper = 0;

Helper *Helper::getInstance()
{
    if(helper == 0)
    {
        helper = new Helper;
    }
    return helper;
}
