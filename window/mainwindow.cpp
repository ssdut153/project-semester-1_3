#include "mainwindow.h"
#include "helper.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent)
{
    this->setMinimumSize(400, 800);
    this->setMaximumSize(400, 800);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    Helper *helper = Helper::getInstance();
    helper->quit();
}
