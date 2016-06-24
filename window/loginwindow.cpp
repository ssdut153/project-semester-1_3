#include "stdafx.h"
#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "tray/trayicon.h"
#include "message/loginmessage.h"
#include "messagebox/exitmessagebox.h"
#include "helper.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow),
    regWindow(0)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    ui->waitingGroupBox->hide();
}

LoginWindow::~LoginWindow()
{
    delete regWindow;
    delete ui;
}

void LoginWindow::on_loginButton_clicked()
{
    QString username = ui->usernameEdit->text();
    QString password = ui->passwordEdit->text();
    if(username == "")
    {
        ui->messageLabel->setText("请输入用户名");
    }
    else if(password == "")
    {
        ui->messageLabel->setText("请输入密码");
    }
    else
    {
        ui->loginGroupBox->hide();
        ui->waitingGroupBox->show();
        ui->messageLabel->clear();
        ui->cancelButton->setFocus();
        loginMessage lm(username.toStdString(), password.toStdString());
        Helper::getInstance()->writeClient(lm);
    }
}

void LoginWindow::on_regButton_clicked()
{
    if(regWindow == 0)
    {
        regWindow = new RegWindow(this);
    }
    regWindow->show();
}

void LoginWindow::on_exitButton_clicked()
{
    if(this->exit())
    {
        CommonElements::getInstance()->trayIcon->hide();
        std::exit(0);
    }
}

void LoginWindow::on_cancelButton_clicked()
{
    ui->waitingGroupBox->hide();
    ui->loginGroupBox->show();
    ui->usernameEdit->setFocus();
}

void LoginWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Enter:
    case Qt::Key_Return:
        if(ui->waitingGroupBox->isHidden())
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

void LoginWindow::clearPasswordEdit()
{
    this->ui->passwordEdit->clear();
}

void LoginWindow::setMessageLabel(const char *message)
{
    this->ui->messageLabel->setText(message);
}

void LoginWindow::keyReleaseEvent(QKeyEvent */*event*/)
{

}

void LoginWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox messageBox(QMessageBox::Warning, "警告", "您真的要退出吗?", 0, 0);
    messageBox.setWindowFlags(Qt::WindowStaysOnTopHint| (this->windowFlags() &~ (Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint)));
    messageBox.addButton("是", QMessageBox::AcceptRole);
    messageBox.addButton("否", QMessageBox::RejectRole);
    if(messageBox.exec() == QMessageBox::RejectRole)
    {
        event->ignore();
    }
    else
    {
        CommonElements::getInstance()->trayIcon->hide();
        std::exit(0);
    }
}

bool LoginWindow::exit()
{
    ExitMessageBox emb;
    bool result = (emb.exec() == QMessageBox::AcceptRole);
    return result;
}
