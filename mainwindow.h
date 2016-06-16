#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "stdafx.h"
#include "ui.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
