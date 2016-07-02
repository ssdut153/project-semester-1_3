#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "stdafx.h"
#include "searchwindow.h"
#include "chatwindow.h"
#include "classes.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    void loadFriendList(QMap<QString, int> &users);
    void setFriendStatus(QString friendName, bool online);
//    void setSearchWindow(SearchWindow *searchWindow);
    QMap<QListWidgetItem*, ChatWindow*> &getChatWindows();
    ChatWindow *getChatWindow(QString friendName);
    SearchWindow *getSearchWindow();
    void addFriendItem(QString friendName, int status);

protected:
    void closeEvent(QCloseEvent *event);

signals:

private:
    QLabel *usernameLabel;
    QListWidget *friendListWidget;
    QPushButton *searchButton;
    QMap<QString, int> friendlist;
    QVector<QListWidgetItem*> items;
    QMap<QListWidgetItem*, ChatWindow*> chatWindows;
    SearchWindow *searchWindow;

private slots:
    void on_searchButton_clicked();
    void on_friendListWidget_doubleClicked(QListWidgetItem *item);

};

#endif // MAINWINDOW_H
