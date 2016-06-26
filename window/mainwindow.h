#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "stdafx.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

protected:
    void closeEvent(QCloseEvent *event);

signals:

public slots:

};

#endif // MAINWINDOW_H
