#include "Loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
#include <cstdlib>
#include <string>
LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_loginButton_clicked()
{
    QMessageBox msgBox(QMessageBox::Warning, tr("Warning"),"功能尚未制作", 0, this);
    msgBox.exec();
}

void LoginWindow::on_regButton_clicked()
{
    QMessageBox msgBox(QMessageBox::Warning, tr("Warning"),"功能尚未制作", 0, this);
    msgBox.exec();
}

void LoginWindow::on_exitButton_clicked()
{
    QMessageBox msgBox(QMessageBox::Warning, tr("Warning"),"您真的要退出吗", 0, this);
    msgBox.addButton(tr("Yes"), QMessageBox::AcceptRole);
    msgBox.addButton(tr("No"), QMessageBox::RejectRole);
    if (msgBox.exec() == QMessageBox::AcceptRole)
        std::exit(0);
}
