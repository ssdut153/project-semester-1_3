#ifndef TRAYICON_H
#define TRAYICON_H

#include "stdafx.h"
#include "classes.h"
#include "messages.h"
#include "traymenu.h"

class TrayIcon : public QSystemTrayIcon
{
    Q_OBJECT

public:
    explicit TrayIcon(QWidget *parent = 0);
    ~TrayIcon();

private:
    TrayMenu *trmn;

private slots:
    void on_trayIcon_clicked(QSystemTrayIcon::ActivationReason reason);

};

#endif // TRAYICON_H
