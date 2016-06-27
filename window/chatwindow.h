#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include "stdafx.h"

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(std::string username, std::string friendName, QWidget *parent = 0);
    ~ChatWindow();

private slots:
    void on_sendButton_clicked();

private:
    Ui::ChatWindow *ui;
    std::string username;
    std::string friendName;
};

#endif // CHATWINDOW_H
