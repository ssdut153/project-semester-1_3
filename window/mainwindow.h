#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidgetItem>
#include "stdafx.h"
#include "ui.h"
#include <string>
#include <vector>
#include "chatwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void loadFriendList(std::vector<std::string> &users, std::vector<int> &onlineStatus);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_friendListWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    std::string username;
    QMap<QString, int> friendlist;
    QListWidgetItem *qlwi;
    QMap<QString, ChatWindow*> chatWindows;

};

#endif // MAINWINDOW_H
