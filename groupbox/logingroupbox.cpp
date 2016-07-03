#include "logingroupbox.h"
#include "commonelements.h"
#include "helper.h"
#include "common/message/loginout/loginmessage.h"
#include "window/loginwindow.h"
#include <QDebug>

LoginGroupBox::LoginGroupBox(QWidget *parent):
    QGroupBox(parent),
    messageLabel(new QLabel(this)),
    usernameEdit(new QLineEdit(this)),
    passwordEdit(new QLineEdit(this)),
    loginButton(new QPushButton(this)),
    regButton(new QPushButton(this)),
    exitButton(new QPushButton(this)),
    regWindow(0)
{
    this->setGeometry(0, 0, 270, 150);

    this->passwordEdit->setEchoMode(QLineEdit::Password);

    this->usernameEdit->setPlaceholderText("请输入用户名");
    this->passwordEdit->setPlaceholderText("请输入密码");
    this->loginButton->setText("登录");
    this->regButton->setText("注册");
    this->exitButton->setText("退出");

    this->messageLabel->setGeometry(30, 10, 210, 20);
    this->usernameEdit->setGeometry(30, 30, 210, 30);
    this->passwordEdit->setGeometry(30, 70, 210, 30);
    this->loginButton->setGeometry(30, 110, 50, 30);
    this->regButton->setGeometry(110, 110, 50, 30);
    this->exitButton->setGeometry(190, 110, 50, 30);

    this->setTabOrder(this->usernameEdit, this->passwordEdit);
    this->setTabOrder(this->passwordEdit, this->loginButton);
    this->setTabOrder(this->loginButton, this->regButton);
    this->setTabOrder(this->regButton, this->exitButton);
    this->setTabOrder(this->exitButton, this->usernameEdit);

    connect(this->loginButton, SIGNAL(clicked()), this, SLOT(on_loginButton_clicked()));
    connect(this->regButton, SIGNAL(clicked()), this, SLOT(on_regButton_clicked()));
    connect(this->exitButton, SIGNAL(clicked()), this, SLOT(on_exitButton_clicked()));

}

void LoginGroupBox::on_loginButton_clicked()
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
        this->hide();
        CommonElements *ce = CommonElements::getInstance();
        ce->getLoginWindow()->getWaitingGroupBox()->show();
        ce->getLoginWindow()->getWaitingGroupBox()->getCancelButton()->setFocus();
        this->messageLabel->clear();
        ce->connectServer();
        loginMessage lm(username, password);
        Helper::getInstance()->writeClient(lm);
    }
}

void LoginGroupBox::on_regButton_clicked()
{
    this->regWindow = new RegWindow(this);
    this->regWindow->show();
}

void LoginGroupBox::on_exitButton_clicked()
{
    Helper *helper = Helper::getInstance();
    helper->quit();
}

void LoginGroupBox::keyPressEvent(QKeyEvent *event)
{
    QWidget *widget = focusWidget();
    switch (event->key()) {
    case Qt::Key_Enter:
    case Qt::Key_Return:
        if(!(this->isHidden() || pressed))
        {
            if(widget == this->usernameEdit || widget == this->passwordEdit || widget == this->loginButton)
            {
                this->on_loginButton_clicked();
            }
            else if(widget == this->regButton)
            {
                this->on_regButton_clicked();
            }
            else if(widget == this->exitButton)
            {
                this->on_exitButton_clicked();
            }
        }
        break;
    }
}

void LoginGroupBox::mousePressEvent(QMouseEvent *event)
{
    place = event->pos();
    pressed = true;
}

void LoginGroupBox::mouseReleaseEvent(QMouseEvent */*event*/)
{
    pressed = false;
}

void LoginGroupBox::mouseMoveEvent(QMouseEvent *event)
{
    QPoint temp = event->pos();
    if(pressed)
    {
        CommonElements *ce = CommonElements::getInstance();
        LoginWindow *lw = ce->getLoginWindow();
        lw->move(lw->x() + temp.x() - this->place.x(), lw->y() + temp.y() - this->place.y());
    }
}

QLabel *LoginGroupBox::getMessageLabel()
{
    return this->messageLabel;
}

QLineEdit *LoginGroupBox::getUsernameEdit()
{
    return this->usernameEdit;
}

QLineEdit *LoginGroupBox::getPasswordEdit()
{
    return this->passwordEdit;
}

RegWindow *LoginGroupBox::getRegWindow()
{
    return this->regWindow;
}

void LoginGroupBox::setRegWindow(RegWindow *regWindow)
{
    this->regWindow = regWindow;
}
