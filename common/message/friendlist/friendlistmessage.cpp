/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: friendlistmessage.cpp
 *  简要描述:
 *
 *  创建日期: 2016-6-24
 *  作者: Yang Zhizhuang
 *  说明:
 *
 *  修改日期:
 *  作者:
 *  说明:
 ****************************************************************************************/
#include "friendlistmessage.h"
/**
 * @brief friendListMessage::friendListMessage
 * @param username 用户名
 */
void friendListMessage::adduser(QString username, int status)
{
    users.insert(username, status);
    size++;
}
/**
 * @brief friendListMessage::friendListMessage
 */
friendListMessage::friendListMessage()
{
    head = "friendList";
    size = 0;
}
/**
 * @brief friendListMessage::getJsonString
 * @return
 */
QString friendListMessage::getJsonString()
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
    QByteArray byteArray = jsonDocument.toJson(QJsonDocument::Compact);
    return QString(byteArray);
}
/**
 * @brief friendListMessage::loadfromJson
 * @param textJson
 * @return
 */
bool friendListMessage::loadfromJson(QString textJson)
{
    QJsonParseError jsonParseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(textJson.toStdString().c_str(), &jsonParseError);
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
