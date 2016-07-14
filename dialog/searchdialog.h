#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include "stdafx.h"
#include "classes.h"
#include "messages.h"
#include "button/closebutton.h"

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(QWidget *parent = 0);
    void showSearchUser(QString searchName);

protected:
    void closeEvent(QCloseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    QLineEdit *searchEdit;
    QPushButton *searchButton;
    QLabel *resultLabel;
    QPushButton *addButton;
    CloseButton *closeButton;
    bool pressed;
    QPoint place;
    QLabel *messageLabel;

private slots:
    void on_searchButton_clicked();
    void on_addButton_clicked();
    void on_closeButton_clicked();

};

#endif // SEARCHDIALOG_H
