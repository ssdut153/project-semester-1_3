#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidgetItem>
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

private slots:
    void switchClicked(QModelIndex);

private:
    Ui::MainWindow *ui;
    std::string username;
    std::vector<std::string> friendlist;
    QListWidgetItem *qlwi;

};

#endif // MAINWINDOW_H
