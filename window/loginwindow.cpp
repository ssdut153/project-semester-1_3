#include "loginwindow.h"
#include "helper.h"
#include "commonelements.h"
#include "common/message/loginout/loginmessage.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    loginGroupBox(new LoginGroupBox(this)),
    waitingGroupBox(new WaitingGroupBox(this))
{
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool | Qt::X11BypassWindowManagerHint);

    this->setWindowTitle("登录");

    this->setMaximumSize(270, 150);
    this->setMinimumSize(270, 150);

}

LoginGroupBox *LoginWindow::getLoginGroupBox()
{
    return this->loginGroupBox;
}

void LoginWindow::loginFail()
{
    CommonElements *ce = CommonElements::getInstance();
    ce->disconnectServer();
    this->loginGroupBox->getPasswordEdit()->clear();
    this->loginGroupBox->getMessageLabel()->setText("用户名或密码错误");
    this->loginGroupBox->show();
    this->waitingGroupBox->hide();
    this->loginGroupBox->getUsernameEdit()->setFocus();
}

WaitingGroupBox *LoginWindow::getWaitingGroupBox()
{
    return this->waitingGroupBox;
}

void LoginWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    Helper *helper = Helper::getInstance();
    helper->quit();
}
