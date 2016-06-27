/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: upmessage.cpp
 *  简要描述:
 *
 *  创建日期: 2016-6-25
 *  作者: Yang Zhizhuang
 *  说明:
 *
 *  修改日期:
 *  作者:
 *  说明:
 ****************************************************************************************/
#include "upmessage.h"
#include "stdafx.h"
/**
 * @brief upMessage::upMessage
 * @param username 用户名
 * @param password 密码
 */
upMessage::upMessage(std::string username,std::string password)
{
    user=username;
    pass=password;
    head="defaulUP";
}
/**
 * @brief upMessage::upMessage
 */
upMessage::upMessage()
{
    head="defaulUP";
}
/**
 * @brief upMessage::getJsonString
 * @return  对应的单行Json字符串
 */
std::string upMessage::getJsonString()
{
    QJsonObject jsonObject;
    jsonObject.insert("head", QString(head.c_str()));
    jsonObject.insert("username", QString(user.c_str()));
    jsonObject.insert("password", QString(pass.c_str()));
    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    QByteArray byteArray = jsonDocument.toJson(QJsonDocument::Compact);
    return byteArray.toStdString();
}
/**
 * @brief upMessage::loadfromJson
 * @param textJson Json字符串
 * @return  bool 是否载入成功
 */
bool upMessage::loadfromJson(std::string textJson)
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
            if(jsonObject.contains("password"))
            {
                QJsonValue passwordValue = jsonObject.take("password");
                if(passwordValue.isString())
                {
                    pass = passwordValue.toString().toStdString();
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

