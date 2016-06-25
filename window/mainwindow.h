#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "stdafx.h"
#include "ui.h"
#include <string>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    std::string username;
};

#endif // MAINWINDOW_H
