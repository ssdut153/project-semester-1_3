#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include "stdafx.h"
#include "classes.h"
#include "mainwindow.h"
#include "commonelements.h"
#include "common/message/function/imagemessage.h"

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(QListWidgetItem *item, MainWindow *parent = 0);
    QTextEdit *getMessageEdit();
    void receivePic(imageMessage im);
    ~ChatWindow();
signals:

protected:
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    QString username;
    QListWidgetItem *item;
    QString friendName;
    QTextEdit *messageEdit;
    QTextEdit *sendEdit;
    QPushButton *sendButton;
    QPushButton *picButton;
    QRadioButton *trueImage;
    QString picPath;
    QString imgTime;
    QNetworkAccessManager *manager;
    QNetworkAccessManager *recmanager;


private slots:
    void on_sendButton_clicked();
    void on_picButton_clicked();
    void onFinished(QNetworkReply *reply);
    void onReceiveFinished(QNetworkReply *reply);

};

#endif // CHATWINDOW_H
