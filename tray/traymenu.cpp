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
#include "traymenu.h"
#include "window/loginwindow.h"
#include "tray/trayicon.h"
#include "helper.h"
#include "common/message/loginout/logoutmessage.h"
#include "commonelements.h"
/**
 * @brief TrayMenu::TrayMenu
 * @param parent 父级元素
 */
TrayMenu::TrayMenu(QWidget *parent):
    QMenu(parent),
    exitAction(new QAction(this))
{
    //    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::X11BypassWindowManagerHint);
    exitAction->setText("退出");
    this->addAction(exitAction);
    connect(exitAction,SIGNAL(triggered()),this,SLOT(on_exitAction_triggered()));
}
/**
 * @brief TrayMenu::~TrayMenu
 */
TrayMenu::~TrayMenu()
{
    delete exitAction;
}
/**
 * @brief TrayMenu::on_exitAction_triggered
 */
void TrayMenu::on_exitAction_triggered()
{
    Helper *helper = Helper::getInstance();
    helper->quit();
}
