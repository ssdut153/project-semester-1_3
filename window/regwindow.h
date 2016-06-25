#ifndef REGWINDOW_H
#define REGWINDOW_H

#include "ui.h"
#include "stdafx.h"

class RegWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegWindow(QWidget *parent = 0);
    ~RegWindow();
    void setMessageLabel(const char *message);
    std::string username;
    std::string password;
    void setRegButtonEnabled(bool enabled);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_regButton_clicked();

private:
    Ui::RegWindow *ui;
};

#endif // REGWINDOW_H
