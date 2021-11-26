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
        FavouriteRole,
        StartCallRole //only used to start call
    };



    // Header:

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override ;

    /*part for call dialog*/
    /*
    Q_PROPERTY(bool callActive READ isCallActive WRITE setEnabled)
    Q_PROPERTY(std::string callerName READ getCallerName)
    Q_PROPERTY(bool callerNumber READ getCallerPhone)*/

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    QHash<int, QByteArray> roleNames() const override;


private:
    std::shared_ptr<FavouritesService> favourites;
    std::unique_ptr<ContactService> contact_service;
    std::unique_ptr<Contact> call_data; // used to pass contact data to call dialog and finish call
    std::unique_ptr<Contact> favourites_dialog_data; //used to pass contact data to favourites dialog and finish call

public:
    Q_PROPERTY(bool favOnly READ getFavOnly WRITE setFavOnly NOTIFY favOnlyChanged);
    Q_PROPERTY(QString search_string READ getSearchString WRITE setSearchString NOTIFY searchStringChanged);

    bool getFavOnly();
    void setFavOnly(bool new_value);
    QString getSearchString();
    void setSearchString(QString new_value);
signals:
    void favOnlyChanged();
    void searchStringChanged();
};
