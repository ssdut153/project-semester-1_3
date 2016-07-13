#ifndef EXPREESSIONWINDOW_H
#define EXPREESSIONWINDOW_H

#include "stdafx.h"
#include "classes.h"
#include "chatwindow.h"

class ExpressionWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ExpressionWindow(ChatWindow *parent = 0);

private:
    QPushButton *comfirmButton;
    QPushButton *cancelButton;
    QComboBox *expressions;
    ChatWindow *chatwindow;

signals:

public slots:
    void on_comfirmButton_clicked();
    void on_cancelButton_clicked();

};

#endif // EXPREESSIONWINDOW_H
