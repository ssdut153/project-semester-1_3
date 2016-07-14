#ifndef LOGINGROUPBOX_H
#define LOGINGROUPBOX_H

#include "stdafx.h"
#include "classes.h"
#include "messages.h"
#include "dialog/regdialog.h"

class LoginGroupBox:public QGroupBox
{
    Q_OBJECT

public:
    explicit LoginGroupBox(QWidget *parent = 0);
    ~LoginGroupBox();
    RegDialog *getRegDialog();
    void setRegDialog(RegDialog *regDialog);
    QLabel *getMessageLabel();
    QLineEdit *getUsernameEdit();
    QLineEdit *getPasswordEdit();

protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QLabel *messageLabel;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
    QPushButton *regButton;
    QLabel *headSculp;
    QLabel *aboutUs;
    RegDialog *regDialog;
    bool pressed;
    QPoint place;

private slots:
    void on_loginButton_clicked();
    void on_regButton_clicked();
    void on_usernameEdit_textChanged();

};

#endif // LOGINGROUPBOX_H
