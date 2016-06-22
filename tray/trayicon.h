#ifndef TRAYICON_H
#define TRAYICON_H

#include "stdafx.h"
#include "traymenu.h"

class TrayIcon : public QSystemTrayIcon
{
    Q_OBJECT

public:
    explicit TrayIcon(QWidget *parent = 0);
    ~TrayIcon();
private:
    TrayMenu *trmn;
};

#endif // TRAYICON_H
