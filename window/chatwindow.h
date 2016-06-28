#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include "ui.h"
#include "stdafx.h"
#include "classes.h"
#include "helper.h"

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(std::string username, QListWidgetItem *item, MainWindow *parent = 0);
    ~ChatWindow();
    void appendText(QString time, QString content);
    void sendFail();
    friend class Helper;

protected:
    void closeEvent(QCloseEvent */*event*/);

private slots:
    void on_sendButton_clicked();

private:
    Ui::ChatWindow *ui;
    std::string username;
    QListWidgetItem *item;
    std::string friendName;
    MainWindow *parent;
};

#endif // CHATWINDOW_H
