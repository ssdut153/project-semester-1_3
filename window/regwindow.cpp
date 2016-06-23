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

void RegWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    this->hide();
}

void RegWindow::on_pushButton_clicked()
{
    if(ui->usernameEdit->text()=="")
    {
        ui->label->setText("请输入用户名");
        return;
    }
    else if(ui->passwordEdit_1->text()=="")
    {
        ui->label->setText("请输入密码");
        return;
    }
    else if(!(ui->passwordEdit_1->text()==ui->passwordEdit_2->text()))
    {
        ui->label->setText("两次输入密码不一致");
        return;
    }
    regUserMessage regusermessage(ui->usernameEdit->text().toStdString(),ui->passwordEdit_1->text().toStdString());
    CommonElements::getInstance()->client->write(regusermessage.getJsonString().c_str());
}
