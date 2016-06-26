/*****************************************************************************************
 *  Copyright(c) 2016 Huwenqiang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: trayicon
 *  简要描述:
 *
 *  创建日期: 2016-6-26
 *  作者: Hu Wenqiang
 *  说明:
 *
 *  修改日期: 2016-6-26
 *  作者: Hu Wenqiang
 *  说明:
 ****************************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "stdafx.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void loadFriendList(std::vector<std::string> &users);

protected:
    void closeEvent(QCloseEvent *event);

private:
    QLabel *usernameLabel;
    QListWidget *friendListWidget;
    std::vector<std::string> friendlist;
    QListWidgetItem *qlwi;

signals:

public slots:

};

#endif // MAINWINDOW_H
