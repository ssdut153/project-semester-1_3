#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "stdafx.h"
#include "helper.h"
#include "regwindow.h"

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();
    bool exit();
    friend class Helper;

protected:
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_loginButton_clicked();
    void on_regButton_clicked();
    void on_exitButton_clicked();
    void on_cancelButton_clicked();

private:
    QGroupBox *loginGroupBox;
    QLabel *messageLabel;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
    QPushButton *regButton;
    QPushButton *exitButton;
    QGroupBox *waitingGroupBox;
    QLabel *waitingLabel;
    QPushButton *cancelButton;
    RegWindow *regWindow;

signals:

public slots:

};

#endif // LOGINWINDOW_H
