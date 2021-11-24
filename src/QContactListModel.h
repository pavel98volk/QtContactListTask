#pragma once
#include <QAbstractListModel>
#include <QList>
#include <memory>
#include "Contact.h"
#include "FavouritesService.h"
#include "ContactService.h"
class QContactListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit QContactListModel(QObject *parent = nullptr);
    enum{
        NameRole = Qt::UserRole,
        NumberRole,
        ImageColorRole,
        ImageHeadTypeRole,
        FavouriteRole
    };
    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    QHash<int, QByteArray> roleNames() const override;

private:
    std::unique_ptr<ContactService> contact_service;
    std::unique_ptr<FavouritesService> favourites;

};
