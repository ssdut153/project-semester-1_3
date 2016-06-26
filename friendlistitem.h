#ifndef FRIENDLISTITEM_H
#define FRIENDLISTITEM_H

#include "stdafx.h"

class FriendListItem:public QListWidgetItem
{
//    Q_OBJECT

public:
    explicit FriendListItem(QListWidget *parent = 0);
    ~FriendListItem();
protected:
    void itemDoubleClicked(QListWidgetItem *item);
};

#endif // FRIENDLISTITEM_H
