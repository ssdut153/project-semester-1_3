#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include "stdafx.h"
#include "classes.h"
#include "messages.h"
#include "commonelements.h"
#include "mainwindow.h"
#include "dialog/expressiondialog.h"

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(QListWidgetItem *item, MainWindow *parent = 0);
    QTextEdit *getMessageEdit();
    void setExpressionDialog(ExpressionDialog *exp);
    void receivePic(imageMessage im);
    void receiveFile(fileMessage fm);
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
    QLabel *friendHead;
    QLabel *friendnameLabel;
    QTextEdit *messageEdit;
    QTextEdit *sendEdit;
    QPushButton *sendButton;
    QPushButton *picButton;
    QPushButton *expressButton;
    QPushButton *filButton;
    CloseButton *closeButton;
    MiniumButton *minButton;
    QString filePath;
    QCheckBox *trueImage;
    QString picPath;
    QString imgTime;
    QString filename;
    QString fileFormalName;
    QString receiveFilename;
    QNetworkAccessManager *manager;
    QNetworkAccessManager *recmanager;
    QNetworkAccessManager *filemanager;
    QNetworkAccessManager *fileRecManager;
    QNetworkAccessManager *dmanager;
    bool pressed;
    QPoint place;
    ExpressionDialog *expDialog;
    QMap<QString,QString> expMap;
    QString dPath;

    void insertExp(QString expKey,QTextCursor cursor);
    void updateFriendHead();

private slots:
    void on_sendButton_clicked();
    void on_picButton_clicked();
    void onFinished(QNetworkReply *reply);
    void onReceiveFinished(QNetworkReply *reply);
    void onFileFinished(QNetworkReply *reply);
    void onFileReceiveFinished(QNetworkReply *reply);
    void onDownloadFinished(QNetworkReply *reply);
    void on_closeButton_clicked();
    void on_expressButton_clicked();
    void on_filButton_clicked();
    void on_minButton_clicked();

};

#endif // CHATWINDOW_H
