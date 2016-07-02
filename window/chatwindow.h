#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include "stdafx.h"
#include "classes.h"
#include "mainwindow.h"
#include "commonelements.h"

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(QListWidgetItem *item, MainWindow *parent = 0);
    QTextEdit *getMessageEdit();

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

private slots:
    void on_sendButton_clicked();

};

#endif // CHATWINDOW_H
