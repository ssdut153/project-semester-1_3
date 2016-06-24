#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "stdafx.h"
#include "ui.h"
#include "commonelements.h"
#include "regwindow.h"
#include "helper.h"

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();
    friend class Helper;
    void clearPasswordEdit();
    void setMessageLabel(const char *message);

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent */*event*/);
    void closeEvent(QCloseEvent *event);

private slots:
    void on_loginButton_clicked();
    void on_regButton_clicked();
    void on_exitButton_clicked();
    void on_cancelButton_clicked();

private:
    bool exit();
    Ui::LoginWindow *ui;
    RegWindow *regWindow;
};

#endif // LOGINWINDOW_H
