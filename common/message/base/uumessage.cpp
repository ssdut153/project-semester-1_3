#include "uumessage.h"

uuMessage::uuMessage(QString fromUserName, QString toUserName)
{
    fromuser = fromUserName;
    touser = toUserName;
    head = "defaultUu";
}

uuMessage::uuMessage()
{
    head = "defaultUu";
}

QByteArray uuMessage::getJsonString()
{
    QJsonObject jsonObject;
    jsonObject.insert("head", head);
    jsonObject.insert("fromusername", fromuser);
    jsonObject.insert("tousername", touser);
    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    return jsonDocument.toJson(QJsonDocument::Compact);
}

bool uuMessage::loadfromJson(QByteArray textJson)
{
    QJsonParseError jsonParseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(textJson, &jsonParseError);
    if(jsonParseError.error == QJsonParseError::NoError)
    {
        if(jsonDocument.isObject())
        {
            QJsonObject jsonObject = jsonDocument.object();
            if(jsonObject.contains("fromusername"))
            {
                QJsonValue jsonValue = jsonObject.take("fromusername");
                if(jsonValue.isString())
                {
                    fromuser = jsonValue.toString();
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
            if(jsonObject.contains("tousername"))
            {
                QJsonValue jsonValue = jsonObject.take("tousername");
                if(jsonValue.isString())
                {
                    touser = jsonValue.toString();
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
