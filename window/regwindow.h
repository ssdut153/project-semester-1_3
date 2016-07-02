#ifndef REGWINDOW_H
#define REGWINDOW_H

#include "stdafx.h"
#include "classes.h"

class RegWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit RegWindow(QWidget *parent = 0);
    QLabel *getMessageLabel();
    QPushButton *getRegButton();
    QString getUsername();
    QString getPassword();

protected:
    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event);

private:
    QLabel *messageLabel;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit_1;
    QLineEdit *passwordEdit_2;
    QPushButton *regButton;
    QString username;
    QString password;

private slots:
    void on_regButton_clicked();

signals:

};

#endif // REGWINDOW_H
