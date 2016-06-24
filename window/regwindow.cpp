#include "regwindow.h"
#include "ui_regwindow.h"
#include "commonelements.h"
#include "message/regusermessage.h"

RegWindow::RegWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegWindow)
{
    ui->setupUi(this);
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

void RegWindow::on_regButton_clicked()
{
    QString username = ui->usernameEdit->text();
    QString password_1 = ui->passwordEdit_1->text();
    QString password_2 = ui->passwordEdit_2->text();
    if(username == "")
    {
        ui->messageLabel->setText("请输入用户名");
    }
    else if(password_1 == "")
    {
        ui->messageLabel->setText("请输入密码");
    }
    else if(!(password_2 == password_1))
    {
        ui->messageLabel->setText("两次输入密码不一致");
    }
    else
    {
        regUserMessage regusermessage(username.toStdString(),password_1.toStdString());

        CommonElements *ce = CommonElements::getInstance();
        ce->connectServer();
        ce->client->write(regusermessage.getJsonString().c_str());
        ui->usernameEdit->clear();
        ui->passwordEdit_1->clear();
        ui->passwordEdit_2->clear();
    }
}
