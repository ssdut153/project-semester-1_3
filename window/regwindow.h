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
#ifndef REGWINDOW_H
#define REGWINDOW_H

#include "stdafx.h"
#include "helper.h"

class RegWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegWindow(QWidget *parent = 0);
    ~RegWindow();
    friend class Helper;

signals:

protected:
    void closeEvent(QCloseEvent *event);

private:
    QLabel *messageLabel;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit_1;
    QLineEdit *passwordEdit_2;
    QPushButton *regButton;
    std::string username;
    std::string password;

private slots:
    void on_regButton_clicked();

public slots:
};

#endif // REGWINDOW_H
