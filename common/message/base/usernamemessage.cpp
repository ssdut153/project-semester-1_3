/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: usernamemessage.cpp
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
#include "usernamemessage.h"
/**
 * @brief usernameMessage::usernameMessage
 * @param username 用户名
 */
usernameMessage::usernameMessage(QString username)
{
    user = username;
    head = "defaultUsername";
}
/**
 * @brief usernameMessage::usernameMessage
 */
usernameMessage::usernameMessage()
{
    head = "defaultUsername";
}
/**
 * @brief usernameMessage::getJsonString
 * @return  对应的单行Json字符串
 */
QString usernameMessage::getJsonString()
{
    QJsonObject jsonObject;
    jsonObject.insert("head", head);
    jsonObject.insert("username", user);
    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    QByteArray byteArray = jsonDocument.toJson(QJsonDocument::Compact);
    return byteArray;
}
/**
 * @brief usernameMessage::loadfromJson
 * @param textJson Json字符串
 * @return  bool 是否载入成功
 */
bool usernameMessage::loadfromJson(QString textJson)
{
    QJsonParseError jsonParseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(textJson.toLatin1(), &jsonParseError);
    if(jsonParseError.error == QJsonParseError::NoError)
    {
        QJsonObject jsonObject  = jsonDocument.object();
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
    }
    else
    {
        return false;
    }
    return true;
}

