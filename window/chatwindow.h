#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include "stdafx.h"
#include "classes.h"
#include "mainwindow.h"
#include "commonelements.h"
#include "common/message/function/imagemessage.h"
#include"expreessionwindow.h"

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(QListWidgetItem *item, MainWindow *parent = 0);
    QTextEdit *getMessageEdit();
    void setExpreessionWindow(ExpreessionWindow* exp);
    void receivePic(imageMessage im);
    QTextEdit* getSendEdit();
    void readContent(QString content);
    ~ChatWindow();

protected:
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QString username;
    QListWidgetItem *item;
    QString friendName;
    QTextEdit *messageEdit;
    QTextEdit *sendEdit;
    QPushButton *sendButton;
    QPushButton *picButton;
    QPushButton *expressButton;
    QPushButton *filButton;
    CloseButton *closeButton;
    QRadioButton *trueImage;
    QString picPath;
    QString imgTime;
    QNetworkAccessManager *manager;
    QNetworkAccessManager *recmanager;
    bool pressed;
    QPoint place;
    ExpreessionWindow *expWindow;
    QMap<QString,QString> expMap;

    void insertExp(QString expKey,QTextCursor cursor);


private slots:
    void on_sendButton_clicked();
    void on_picButton_clicked();
    void onFinished(QNetworkReply *reply);
    void onReceiveFinished(QNetworkReply *reply);
    void on_closeButton_clicked();
    void on_expressButton_clicked();
    void on_filButton_clicked();

};

#endif // CHATWINDOW_H
