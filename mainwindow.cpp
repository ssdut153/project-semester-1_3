#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <cstdlib>
#include <string>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginButton_clicked()
{
    QMessageBox msgBox(QMessageBox::Warning, tr("Warning"),"功能尚未制作", 0, this);
    msgBox.exec();
}

void MainWindow::on_regButton_clicked()
{
    QMessageBox msgBox(QMessageBox::Warning, tr("Warning"),"功能尚未制作", 0, this);
    msgBox.exec();
}

void MainWindow::on_exitButton_clicked()
{
    QMessageBox msgBox(QMessageBox::Warning, tr("Warning"),"您真的要退出吗", 0, this);
    msgBox.addButton(trUtf8("是"), QMessageBox::AcceptRole);
    msgBox.addButton(tr("No"), QMessageBox::RejectRole);
    if (msgBox.exec() == QMessageBox::AcceptRole)
        std::exit(0);
}
