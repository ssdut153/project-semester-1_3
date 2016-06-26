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
#include "loginwindow.h"
#include "commonelements.h"
#include "common/message/loginout/loginmessage.h"
#include "helper.h"
/**
 * @brief LoginWindow::LoginWindow
 * @param parent 父级元素
 */
LoginWindow::LoginWindow(QWidget *parent):
    QMainWindow(parent),
    loginGroupBox(new QGroupBox(this)),
    messageLabel(new QLabel(loginGroupBox)),
    usernameEdit(new QLineEdit(loginGroupBox)),
    passwordEdit(new QLineEdit(loginGroupBox)),
    loginButton(new QPushButton(loginGroupBox)),
    regButton(new QPushButton(loginGroupBox)),
    exitButton(new QPushButton(loginGroupBox)),
    waitingGroupBox(new QGroupBox(this)),
    waitingLabel(new QLabel(waitingGroupBox)),
    cancelButton(new QPushButton(waitingGroupBox)),
    regWindow(new RegWindow(this))
{
    this->setWindowTitle("登录");

    this->setWindowFlags(Qt::WindowStaysOnTopHint);

    this->setMaximumSize(270, 150);
    this->setMinimumSize(270, 150);

    this->loginGroupBox->setGeometry(0, 0, 270, 150);
    this->messageLabel->setGeometry(40, 5, 190, 30);
    this->usernameEdit->setGeometry(40, 30, 190, 30);
    this->passwordEdit->setGeometry(40,70,190, 30);
    this->loginButton->setGeometry(40, 110, 50, 30);
    this->regButton->setGeometry(110, 110, 50, 30);
    this->exitButton->setGeometry(180, 110, 50, 30);
    this->waitingGroupBox->setGeometry(0, 0, 270, 150);
    this->waitingLabel->setGeometry(110, 50, 100, 30);
    this->cancelButton->setGeometry(110, 110, 50, 30);

    this->usernameEdit->setPlaceholderText("请输入用户名");
    this->passwordEdit->setPlaceholderText("请输入密码");

    this->passwordEdit->setEchoMode(QLineEdit::Password);

    this->loginButton->setText("登录");
    this->regButton->setText("注册");
    this->exitButton->setText("退出");
    this->waitingLabel->setText("正在登录");
    this->cancelButton->setText("取消");

    this->waitingGroupBox->hide();
    this->regWindow->hide();

    connect(loginButton, SIGNAL(clicked(bool)), this, SLOT(on_loginButton_clicked()));
    connect(regButton, SIGNAL(clicked(bool)), this, SLOT(on_regButton_clicked()));
    connect(exitButton, SIGNAL(clicked(bool)), this, SLOT(on_exitButton_clicked()));
    connect(cancelButton, SIGNAL(clicked(bool)), this,SLOT(on_cancelButton_clicked()));
}
/**
 * @brief LoginWindow::~LoginWindow
 */
LoginWindow::~LoginWindow()
{

}
/**
 * @brief LoginWindow::on_loginButton_clicked
 */
void LoginWindow::on_loginButton_clicked()
{
    QString username = this->usernameEdit->text();
    QString password = this->passwordEdit->text();
    if(username == "")
    {
        this->messageLabel->setText("请输入用户名");
    }
    else if(password == "")
    {
        this->messageLabel->setText("请输入密码");
    }
    else
    {
        this->loginGroupBox->hide();
        this->waitingGroupBox->show();
        this->messageLabel->clear();
        this->cancelButton->setFocus();
        CommonElements *ce = CommonElements::getInstance();
        loginMessage lm(username.toStdString(), password.toStdString());
        ce->connectServer();
        Helper::getInstance()->writeClient(lm);
    }
}
/**
 * @brief LoginWindow::on_regButton_clicked
 */
void LoginWindow::on_regButton_clicked()
{
    regWindow = new RegWindow(this);
    regWindow->show();
}
/**
 * @brief LoginWindow::on_exitButton_clicked
 */
void LoginWindow::on_exitButton_clicked()
{
    Helper *helper = Helper::getInstance();
    helper->quit();
}
/**
 * @brief LoginWindow::on_cancelButton_clicked
 */
void LoginWindow::on_cancelButton_clicked()
{
    CommonElements *ce = CommonElements::getInstance();
    ce->disconnectServer();
    this->waitingGroupBox->hide();
    this->loginGroupBox->show();
    this->usernameEdit->setFocus();
}
/**
 * @brief LoginWindow::closeEvent
 * @param event
 */
void LoginWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    Helper *helper = Helper::getInstance();
    helper->quit();
}
/**
 * @brief LoginWindow::keyPressEvent
 * @param event
 */
void LoginWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Enter:
    case Qt::Key_Return:
        if(this->waitingGroupBox->isHidden())
        {
            this->on_loginButton_clicked();
        }
        else
        {
            this->on_cancelButton_clicked();
        }
        break;
    default:
        break;
    }
}
