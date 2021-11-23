#include "QContactListModel.h"
#include <QFile>
#include <QFileInfo>
QContactListModel::QContactListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    this->contact_service = std::make_unique<ContactListProviderFromFile>(":/resources/contacts.txt");
    std::vector<SimpleContact> contacts = this->contact_service->getContacts();
    for (SimpleContact& simple_contact : contacts){
        this->contact_list.append(Contact(simple_contact.getName(),simple_contact.getNumber(),false));
    }
}

QVariant QContactListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
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

    return this->contact_list.length();
    // FIXME: Implement me!
}

QVariant QContactListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(role){
    case NameRole:
        return QVariant(QString::fromStdString(this->contact_list[index.row()].getName()));
    case NumberRole:
        return QVariant(QString::fromStdString(this->contact_list[index.row()].getNumber()));
    case ImageColorRole:
        return QVariant(QString::fromStdString(this->contact_list[index.row()].getImageColor()));
    case ImageHeadTypeRole:
        return QVariant(this->contact_list[index.row()].getHeadType());
    case FavouriteRole:
        return QVariant(this->contact_list[index.row()].getFavourite());

    }

    return QVariant();
}

bool QContactListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
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
    return roles;
}
