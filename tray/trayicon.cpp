/*****************************************************************************************
 *  Copyright(c) 2016 Huwenqiang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: trayicon
 *  简要描述:
 *
 *  创建日期: 2016-6-21
 *  作者: Hu Wenqiang
 *  说明:
 *
 *  修改日期: 2016-6-21
 *  作者: Hu Wenqiang
 *  说明:
 ****************************************************************************************/
#include "stdafx.h"
#include "trayicon.h"
#include "traymenu.h"
/**
 * @brief TrayIcon::TrayIcon
 * @param parent 父级元素
 */
TrayIcon::TrayIcon(QWidget *parent):
    QSystemTrayIcon(parent)
{
    this->setToolTip("聊天工具");
    this->setIcon(QIcon(":/images/icon"));

    this->trmn = new TrayMenu;
    this->setContextMenu(trmn);
}
/**
 * @brief TrayIcon::~TrayIcon
 */
TrayIcon::~TrayIcon()
{
    delete trmn;
}
