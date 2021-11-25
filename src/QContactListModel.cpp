#include "QContactListModel.h"
#include <QFile>
#include<QDebug>
#include <QFileInfo>

QContactListModel::QContactListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    this->favourites = std::make_shared<FavouritesServiceFromFile>("./fav.txt");
    this->favourites->load();

    this->contact_service = std::make_unique<CachedSearchableContactService>(this->favourites,":/resources/contacts.txt");
}

QVariant QContactListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch(section){
        case 0: // favourites filter status
            return this->contact_service->getFavFilterStatus();
        case 1: // search string value
            return QVariant(QString::fromStdString(this->contact_service->getSearchString()));
    }
}

bool QContactListModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (value != headerData(section, orientation, role)) {
        // FIXME: Implement me!
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}

int QContactListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return this->contact_service->list_length();
    // FIXME: Implement me!
}

QVariant QContactListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(role){
    case NameRole:
        return QVariant(QString::fromStdString(this->contact_service->get(index.row()).getName()));
    case NumberRole:
        return QVariant(QString::fromStdString(this->contact_service->get(index.row()).getNumber()));
    case ImageColorRole:
        return QVariant(QString::fromStdString(this->contact_service->get(index.row()).getImageColor()));
    case ImageHeadTypeRole:
        return QVariant(this->contact_service->get(index.row()).getHeadType());
    case FavouriteRole:
        return QVariant(favourites->contains(this->contact_service->get(index.row()).getName()));
    }

    return QVariant();
}

bool QContactListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        if(role == FavouriteRole){
            if(value == true){
                favourites->insert(this->contact_service->get(index.row()).getName());
            } else {
              favourites->remove(this->contact_service->get(index.row()).getName());
            }
            emit dataChanged(index, index, QVector<int>() << role);
            return true;
        }
    }
    return false;
}

Qt::ItemFlags QContactListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> QContactListModel::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles[NameRole] = "name";
    roles[NumberRole] = "number";
    roles[ImageColorRole] = "imageColor";
    roles[ImageHeadTypeRole] = "imageHeadType";
    roles[FavouriteRole] = "favourite";
    roles[StartCallRole] = "startCall";

    return roles;
}
/*
void QContactListModel::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(new QAction("Action 1", this));
    menu.addAction(new QAction("Action 2", this));
    menu.addAction(new QAction("Action 3", this));

    // Place the menu in the right position and show it.
    menu.exec(event->globalPos());
}*/
