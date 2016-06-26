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
#include "regwindow.h"
#include "common/message/reg/regusermessage.h"
#include "commonelements.h"
/**
 * @brief RegWindow::RegWindow
 * @param parent
 */
RegWindow::RegWindow(QWidget *parent):
    QMainWindow(parent),
    messageLabel(new QLabel(this)),
    usernameEdit(new QLineEdit(this)),
    passwordEdit_1(new QLineEdit(this)),
    passwordEdit_2(new QLineEdit(this)),
    regButton(new QPushButton(this))
{
    this->setWindowModality(Qt::ApplicationModal);

    this->setWindowTitle("注册");

    this->setMaximumSize(270, 200);
    this->setMinimumSize(270, 200);

    this->messageLabel->setGeometry(40, 0, 200, 20);
    this->usernameEdit->setGeometry(40, 30, 200, 30);
    this->passwordEdit_1->setGeometry(40, 70 , 200, 30);
    this->passwordEdit_2->setGeometry(40, 110, 200, 30);
    this->regButton->setGeometry(40, 150, 200, 30);

    this->messageLabel->setText("");
    this->usernameEdit->setPlaceholderText("请输入用户名");
    this->passwordEdit_1->setPlaceholderText("请输入密码");
    this->passwordEdit_2->setPlaceholderText("请确认密码");

    this->passwordEdit_1->setEchoMode(QLineEdit::Password);
    this->passwordEdit_2->setEchoMode(QLineEdit::Password);

    this->regButton->setText("注册");

    connect(regButton, SIGNAL(clicked(bool)), this, SLOT(on_regButton_clicked()));

}
/**
 * @brief RegWindow::on_regButton_clicked
 */
void RegWindow::on_regButton_clicked()
{
    QString username = this->usernameEdit->text();
    QString password_1 = this->passwordEdit_1->text();
    QString password_2 = this->passwordEdit_2->text();
    if(username == "")
    {
        this->messageLabel->setText("请输入用户名");
    }
    else if(username.length() < 3 || username.length() > 20)
    {
        this->messageLabel->setText("用户名应在3-20位");
    }
    else if(password_1 == "")
    {
        this->messageLabel->setText("请输入密码");
    }
    else if(password_1.length() < 6 || password_1.length() > 16)
    {
        this->messageLabel->setText("密码应在6-16位");
    }
    else if(!(password_2 == password_1))
    {
        this->messageLabel->setText("两次输入密码不一致");
    }
    else
    {
        this->regButton->setEnabled(false);
        regUserMessage rum(username.toStdString(),password_1.toStdString());
        CommonElements *ce = CommonElements::getInstance();
        this->username = username.toStdString();
        this->password = password_1.toStdString();
        ce->connectServer();
        Helper::getInstance()->writeClient(rum);
    }
}
/**
 * @brief RegWindow::closeEvent
 */
void RegWindow::closeEvent(QCloseEvent *)
{
    delete this;
}
/**
 * @brief RegWindow::~RegWindow
 */
RegWindow::~RegWindow()
{

}
