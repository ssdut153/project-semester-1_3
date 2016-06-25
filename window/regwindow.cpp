#include "regwindow.h"
#include "ui_regwindow.h"
#include "commonelements.h"
#include "message/regusermessage.h"

RegWindow::RegWindow(QWidget *parent) :
    QMainWindow(parent),
    username(""),
    password(""),
    ui(new Ui::RegWindow)
{
    ui->setupUi(this);
    this->setWindowModality(Qt::ApplicationModal);
}

RegWindow::~RegWindow()
{
    delete ui;
}

void RegWindow::setMessageLabel(const char *message)
{
    this->ui->messageLabel->setText(message);
}

void RegWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    delete this;
}

void RegWindow::setRegButtonEnabled(bool enabled)
{
    ui->regButton->setEnabled(enabled);
}

void RegWindow::on_regButton_clicked()
{
    QString username = ui->usernameEdit->text();
    QString password_1 = ui->passwordEdit_1->text();
    QString password_2 = ui->passwordEdit_2->text();
    if(username == "")
    {
        ui->messageLabel->setText("请输入用户名");
    }
    else if(username.length() < 3 || username.length() > 20)
    {
        ui->messageLabel->setText("用户名应在3-20位");
    }
    else if(password_1 == "")
    {
        ui->messageLabel->setText("请输入密码");
    }
    else if(password_1.length() < 6 || password_1.length() > 16)
    {
        ui->messageLabel->setText("密码应在6-16位");
    }
    else if(!(password_2 == password_1))
    {
        ui->messageLabel->setText("两次输入密码不一致");
    }
    else
    {
        ui->regButton->setEnabled(false);
        regUserMessage rum(username.toStdString(),password_1.toStdString());
        CommonElements *ce = CommonElements::getInstance();
        this->username = username.toStdString();
        this->password = password_1.toStdString();
        ce->connectServer();
        Helper::getInstance()->writeClient(rum);
    }
}
