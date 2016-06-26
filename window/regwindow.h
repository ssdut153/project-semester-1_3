#ifndef REGWINDOW_H
#define REGWINDOW_H

#include "stdafx.h"
#include "helper.h"

class RegWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegWindow(QWidget *parent = 0);
    friend class Helper;

signals:

private:
    QLabel *messageLabel;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit_1;
    QLineEdit *passwordEdit_2;
    QPushButton *regButton;
    std::string username;
    std::string password;

private slots:
    void on_regButton_clicked();

public slots:
};

#endif // REGWINDOW_H
