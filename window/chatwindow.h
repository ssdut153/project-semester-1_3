#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include "stdafx.h"

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(std::string username, std::string friendName, QWidget *parent = 0);
    ~ChatWindow();

private:
    std::string username;
    std::string friendName;
    QTextEdit *messageEdit;
    QTextEdit *sendEdit;
    QPushButton *sendButton;

private slots:
    void on_sendButton_clicked();

signals:

public slots:
};

#endif // CHATWINDOW_H
