#include "upmessage.h"

upMessage::upMessage(QString username, QString password)
{
    user = username;
    pass = password;
    head = "defaulUP";
}

upMessage::upMessage()
{
    head="defaulUP";
}

QByteArray upMessage::getJsonString()
{
    QJsonObject jsonObject;
    jsonObject.insert("head", head);
    jsonObject.insert("username", user);
    jsonObject.insert("password", pass);
    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    return jsonDocument.toJson(QJsonDocument::Compact);
}

bool upMessage::loadfromJson(QByteArray textJson)
{
    QJsonParseError jsonParseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(textJson, &jsonParseError);
    if(jsonParseError.error == QJsonParseError::NoError)
    {
        if(jsonDocument.isObject())
        {
            QJsonObject jsonObject = jsonDocument.object();
            if(jsonObject.contains("username"))
            {
                QJsonValue jsonValue = jsonObject.take("username");
                if(jsonValue.isString())
                {
                    user = jsonValue.toString();
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
            if(jsonObject.contains("password"))
            {
                QJsonValue jsonValue = jsonObject.take("password");
                if(jsonValue.isString())
                {
                    pass = jsonValue.toString();
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    return true;
}

