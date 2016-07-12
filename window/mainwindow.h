#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "stdafx.h"
#include "classes.h"
#include "searchwindow.h"
#include "chatwindow.h"
#include "button/closebutton.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void loadFriendList(QMap<QString, int> &users);
    void setFriendStatus(QString friendName, bool online);
//    void setSearchWindow(SearchWindow *searchWindow);
    QMap<QListWidgetItem*, ChatWindow*> &getChatWindows();
    ChatWindow *getChatWindow(QString friendName);
    SearchWindow *getSearchWindow();
    void addFriendItem(QString friendName, int status);
    void updateHeadSculp();
    void downloadHeadSculp();

protected:
    void closeEvent(QCloseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QLabel *usernameLabel;
    QListWidget *friendListWidget;
    QPushButton *searchButton;
    QPushButton *headButton;
    CloseButton *closeButton;
    QLabel *headSculp;
    QMap<QString, int> friendlist;
    QVector<QListWidgetItem*> items;
    QMap<QListWidgetItem*, ChatWindow*> chatWindows;
    SearchWindow *searchWindow;
    bool pressed;
    QPoint place;
    QNetworkAccessManager *umanager;
    QNetworkAccessManager *dmanager;
    QString dPath;
    QString picPath;

private slots:
    void on_searchButton_clicked();
    void on_friendListWidget_doubleClicked(QListWidgetItem *item);
    void on_closeButton_clicked();
    void on_headButton_clicked();
    void onUploadFinished(QNetworkReply *reply);
    void onDownloadFinished(QNetworkReply *reply);

};

#endif // MAINWINDOW_H
