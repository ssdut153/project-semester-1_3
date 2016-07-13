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
    MiniumButton *minButton;
    QRadioButton *trueImage;
    QString picPath;
    QString imgTime;
    QNetworkAccessManager *manager;
    QNetworkAccessManager *recmanager;
    bool pressed;
    QPoint place;

private slots:
    void on_sendButton_clicked();
    void on_picButton_clicked();
    void onFinished(QNetworkReply *reply);
    void onReceiveFinished(QNetworkReply *reply);
    void on_closeButton_clicked();
    void on_expressButton_clicked();
    void on_filButton_clicked();
    void on_minButton_clicked();

};

#endif // CHATWINDOW_H
