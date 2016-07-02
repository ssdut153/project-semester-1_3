#include "loginwindow.h"
#include "helper.h"
#include "commonelements.h"
#include "common/message/loginout/loginmessage.h"

LoginWindow::LoginWindow(QWidget *parent) :
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
    regWindow(0)
{
    this->setWindowFlags(Qt::WindowStaysOnTopHint);

    this->setWindowTitle("登录");

    this->setMaximumSize(270, 150);
    this->setMinimumSize(270, 150);

    this->usernameEdit->setFocus();
    this->passwordEdit->setEchoMode(QLineEdit::Password);

    this->usernameEdit->setPlaceholderText("请输入用户名");
    this->passwordEdit->setPlaceholderText("请输入密码");
    this->loginButton->setText("登录");
    this->regButton->setText("注册");
    this->exitButton->setText("退出");
    this->waitingLabel->setText("正在登录");
    this->cancelButton->setText("取消");

    this->setTabOrder(this->usernameEdit, this->passwordEdit);
    this->setTabOrder(this->passwordEdit, this->loginButton);
    this->setTabOrder(this->loginButton, this->regButton);
    this->setTabOrder(this->regButton, this->exitButton);
    this->setTabOrder(this->exitButton, this->usernameEdit);
    this->setTabOrder(this->cancelButton, this->cancelButton);

    this->loginGroupBox->setGeometry(0, 0, 270, 150);

    this->messageLabel->setGeometry(30, 10, 210, 20);
    this->usernameEdit->setGeometry(30, 30, 210, 30);
    this->passwordEdit->setGeometry(30, 70, 210, 30);
    this->loginButton->setGeometry(30, 110, 50, 30);
    this->regButton->setGeometry(110, 110, 50, 30);
    this->exitButton->setGeometry(190, 110, 50, 30);

    this->waitingGroupBox->setGeometry(0, 0, 270, 150);

    this->waitingLabel->setGeometry(100, 40, 60, 30);
    this->cancelButton->setGeometry(110, 90, 50, 30);

    this->waitingGroupBox->hide();

    connect(this->loginButton, SIGNAL(clicked()), this, SLOT(on_loginButton_clicked()));
    connect(this->regButton, SIGNAL(clicked()), this, SLOT(on_regButton_clicked()));
    connect(this->exitButton, SIGNAL(clicked()), this, SLOT(on_exitButton_clicked()));
    connect(this->cancelButton, SIGNAL(clicked()), this, SLOT(on_cancelButton_clicked()));

}

void LoginWindow::keyPressEvent(QKeyEvent *event)
{
    QWidget *widget = focusWidget();
    switch (event->key()) {
    case Qt::Key_Enter:
    case Qt::Key_Return:
        if(this->waitingGroupBox->isHidden())
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
        else
        {
            this->on_cancelButton_clicked();
        }
        break;
    }
}

void LoginWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    Helper *helper = Helper::getInstance();
    helper->quit();
}

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
        ce->connectServer();
        loginMessage lm(username, password);
        Helper::getInstance()->writeClient(lm);
    }
}

void LoginWindow::on_regButton_clicked()
{
    this->regWindow = new RegWindow(this);
    this->regWindow->show();
}

void LoginWindow::on_exitButton_clicked()
{
    Helper *helper = Helper::getInstance();
    helper->quit();
}

void LoginWindow::on_cancelButton_clicked()
{
    this->waitingGroupBox->hide();
    this->loginGroupBox->show();
    this->usernameEdit->setFocus();
}

RegWindow *LoginWindow::getRegWindow()
{
    return this->regWindow;
}

void LoginWindow::setRegWindow(RegWindow *regWindow)
{
    this->regWindow = regWindow;
}

QLabel *LoginWindow::getMessageLabel()
{
    return this->messageLabel;
}

QLineEdit *LoginWindow::getPasswordEdit()
{
    return this->passwordEdit;
}

void LoginWindow::cancelLogin()
{
    this->on_cancelButton_clicked();
}
