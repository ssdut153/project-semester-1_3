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
    this->hide();
}

void RegWindow::on_regButton_clicked()
{
    if(ui->usernameEdit->text()=="")
    {
        ui->messageLabel->setText("请输入用户名");
        return;
    }
    else if(ui->passwordEdit_1->text()=="")
    {
        ui->messageLabel->setText("请输入密码");
        return;
    }
    else if(!(ui->passwordEdit_1->text()==ui->passwordEdit_2->text()))
    {
        ui->messageLabel->setText("两次输入密码不一致");
        return;
    }
    regUserMessage regusermessage(ui->usernameEdit->text().toStdString(),ui->passwordEdit_1->text().toStdString());
    CommonElements::getInstance()->client->write(regusermessage.getJsonString().c_str());
    ui->usernameEdit->clear();
    ui->passwordEdit_1->clear();
    ui->passwordEdit_2->clear();
}
