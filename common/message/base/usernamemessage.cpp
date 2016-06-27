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
#include "stdafx.h"
#include "common/cJSON.h"
/**
 * @brief usernameMessage::usernameMessage
 * @param username 用户名
 */
usernameMessage::usernameMessage(std::string username)
{
    user=username;
    head="defaultUsername";
}
/**
 * @brief usernameMessage::usernameMessage
 */
usernameMessage::usernameMessage()
{
    head="defaultUsername";
}
/**
 * @brief usernameMessage::getJsonString
 * @return  对应的单行Json字符串
 */
std::string usernameMessage::getJsonString()
{
    QJsonObject jsonObject;
    jsonObject.insert("head", QString(head.c_str()));
    jsonObject.insert("username", QString(user.c_str()));
    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    QByteArray byteArray = jsonDocument.toJson(QJsonDocument::Compact);
    return byteArray.toStdString();
}
/**
 * @brief usernameMessage::loadfromJson
 * @param textJson Json字符串
 * @return  bool 是否载入成功
 */
bool usernameMessage::loadfromJson(std::string textJson)
{
    QJsonParseError parseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QString(textJson.c_str()).toLatin1(), &parseError);
    if(parseError.error == QJsonParseError::NoError)
    {
        if(jsonDocument.isObject())
        {
            QJsonObject jsonObject = jsonDocument.object();
            if(jsonObject.contains("username"))
            {
                QJsonValue usernameValue = jsonObject.take("username");
                if(usernameValue.isString())
                {
                    user = usernameValue.toString().toStdString();
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

