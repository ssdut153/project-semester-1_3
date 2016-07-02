#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include "stdafx.h"

class SearchWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit SearchWindow(QWidget *parent = 0);
    void showSearchUser(QString searchName);

protected:
    void closeEvent(QCloseEvent *event);

signals:

private:
    QLineEdit *searchEdit;
    QPushButton *searchButton;
    QLabel *resultLabel;
    QPushButton *addButton;

private slots:
    void on_searchButton_clicked();
    void on_addButton_clicked();

};

#endif // SEARCHWINDOW_H
