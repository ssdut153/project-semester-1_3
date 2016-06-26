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
 *  修改日期: 2016-6-26
 *  作者: Hu Wenqiang
 *  说明:
 ****************************************************************************************/
#ifndef TRAYMENU_H
#define TRAYMENU_H

#include "stdafx.h"

class TrayMenu : public QMenu
{
    Q_OBJECT

private:
    QAction *exitAction;

public:
    explicit TrayMenu(QWidget *parent = 0);
    ~TrayMenu();
private slots:
    void on_exitAction_triggered();
protected:
//    void paintEvent(QPaintEvent *event);
};

#endif // TRAYMENU_H
