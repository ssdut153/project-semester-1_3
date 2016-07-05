#include "friendlistmessage.h"

void friendListMessage::adduser(QString username, int status)
{
    users.insert(username, status);
    size++;
}

friendListMessage::friendListMessage()
{
    head = "friendList";
    size = 0;
}

QByteArray friendListMessage::getJsonString()
{
    QJsonArray jsonArray;
    for(QMap<QString, int>::iterator it = users.begin();it != users.end(); it++)
    {
        QJsonObject jsonObject;
        jsonObject.insert("username", it.key());
        jsonObject.insert("status", it.value());
        jsonArray.push_back(jsonObject);
        QJsonDocument tempJsonDocument;
        tempJsonDocument.setObject(jsonObject);
        jsonArray.push_back(QString(tempJsonDocument.toJson(QJsonDocument::Compact)));
    }
    QJsonDocument jsonDocument;
    jsonDocument.setArray(jsonArray);
    return jsonDocument.toJson(QJsonDocument::Compact);
}

bool friendListMessage::loadfromJson(QByteArray textJson)
{
    QJsonParseError jsonParseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(textJson, &jsonParseError);
    if(jsonParseError.error == QJsonParseError::NoError)
    {
        if(jsonDocument.isArray())
        {
            QJsonArray jsonArray = jsonDocument.array();
            size = jsonArray.size();
            for(int i = 0;i < size;i++)
            {
                QJsonValue jsonValue = jsonArray.at(i);
                if(jsonValue.isObject())
                {
                    QJsonObject tempJsonObject =jsonValue.toObject();
                    if(tempJsonObject.contains("username") && tempJsonObject.contains("status"))
                    {
                        QJsonValue usernameValue = tempJsonObject.take("username");
                        QJsonValue statusValue = tempJsonObject.take("status");
                        if(usernameValue.isString() && statusValue.isDouble())
                        {
                            users.insert(usernameValue.toString(), statusValue.toInt());
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
