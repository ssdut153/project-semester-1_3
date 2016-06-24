#include "helper.h"
#include "commonelements.h"

Helper::Helper():
    client(CommonElements::getInstance()->client)
{
    connect(client, SIGNAL(readyRead()), this, SLOT(readClient()));
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
    std::string head = this->getfromJson(str.toStdString(), "head");
    if(head == "loginFeedBack")
    {
        std::string status = this->getfromJson(str.toStdString(), "status");
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
            ce->loginWindow->on_cancelButton_clicked();
            ce->loginWindow->clearPasswordEdit();
            ce->loginWindow->setMessageLabel("用户名或密码错误");
        }
    }
    else if(head == "regFeedBack")
    {

    }
}

void Helper::writeClient(Message &message)
{
    CommonElements::getInstance()->client->write(message.getJsonString().c_str());
    qDebug()<<"test2";
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
