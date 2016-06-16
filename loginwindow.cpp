#include "stdafx.h"
#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setMouseTracking(true);
    ui->cancelButton->hide();
    ui->loginLabel->hide();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_loginButton_clicked()
{
    ui->loginButton->hide();
    ui->usernameEdit->hide();
    ui->passwordEdit->hide();
    ui->regButton->hide();
    ui->exitButton->hide();
    ui->loginLabel->show();
    ui->cancelButton->show();
//    MainWindow *w = new MainWindow;
//    w->show();
}

void LoginWindow::on_regButton_clicked()
{

}

void LoginWindow::on_exitButton_clicked()
{
    QString str;
    QMessageBox msgBox(QMessageBox::Warning, tr("Warning"),"您真的要退出吗", 0, this);
    msgBox.addButton(tr("Yes"), QMessageBox::AcceptRole);
    msgBox.addButton(tr("No"), QMessageBox::RejectRole);
    if (msgBox.exec() == QMessageBox::AcceptRole)
        std::exit(0);
}

void LoginWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        mouse_press = true;
        move_point = event->pos();
    }
}

void LoginWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        mouse_press = false;
        move_point = event->pos();
    }
}

void LoginWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (mouse_press)
    {
        QPoint move_pos = event->globalPos();
        this->move(move_pos-move_point);
    }
}

void LoginWindow::on_cancelButton_clicked()
{
    ui->loginButton->show();
    ui->regButton->show();
    ui->exitButton->show();
    ui->usernameEdit->show();
    ui->passwordEdit->show();
    ui->loginLabel->hide();
    ui->cancelButton->hide();
}
