#include "friendlistitem.h"
#include <QDebug>

FriendListItem::FriendListItem(QListWidget *parent):
    QListWidgetItem(parent)
{

}

FriendListItem::~FriendListItem()
{

}

void FriendListItem::itemDoubleClicked(QListWidgetItem *item)
{
    qDebug()<<"test";
}
