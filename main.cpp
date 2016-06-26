/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: trayicon
 *  简要描述:
 *
 *  创建日期: 2016-6-16
 *  作者: Yang Zhizhuang
 *  说明:
 *
 *  修改日期: 2016-6-26
 *  作者: Hu Wenqiang
 *  说明:
 ****************************************************************************************/
#include "stdafx.h"
#include "tray/trayicon.h"
#include "window/loginwindow.h"
#include "commonelements.h"
/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    QApplication *a = new QApplication(argc, argv);

    a->setWindowIcon(QIcon(":/images/icon"));

    TrayIcon *ti = new TrayIcon;
    LoginWindow *lw = new LoginWindow;
    CommonElements *ce = CommonElements::getInstance();

    ce->trayIcon = ti;
    ce->application = a;
    ce->loginWindow = lw;

    ti->show();
    lw->show();
    return a->exec();
}
