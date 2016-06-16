#include <cstdlib>
#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setMouseTracking(true);
    ui->loginGroupBox->hide();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_loginButton_clicked()
{
    ui->inputGroupBox->hide();
    ui->loginGroupBox->show();
}

void LoginWindow::on_regButton_clicked()
{

}

void LoginWindow::on_exitButton_clicked()
{
    QMessageBox msgBox(QMessageBox::Warning, tr("Warning"),"您真的要退出吗", 0, this);
    //msgBox.setStyleSheet("");
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

void LoginWindow::on_pushButton_clicked()
{
    ui->loginGroupBox->hide();
    ui->inputGroupBox->show();
}
