#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "stdafx.h"
#include "ui.h"
#include <string>
#include <vector>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void loadFriendList(std::vector<std::string> &users);

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    std::string username;
    std::vector<std::string> friendlist;
};

#endif // MAINWINDOW_H
