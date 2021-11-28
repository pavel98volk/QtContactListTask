#ifndef FAVOURITESSERVICE_H
#define FAVOURITESSERVICE_H
#include <QString>
#include <unordered_set>
#include "utils.h"

class FavouritesService
{
public:
    virtual void insert(QString name) = 0;
    virtual void remove(QString name) = 0;
    virtual bool contains(QString name) = 0;
    enum CHANGE_TYPE {Insert, Remove, UpdateAll};
    virtual int listenToChange(std::function<void(FavouritesService::CHANGE_TYPE, QString)>) = 0;
    virtual void removeListener(int) = 0;

    virtual void store() = 0;
    virtual void load() = 0;
};
class FavouritesServiceFromFile: public FavouritesService
{
public:
    FavouritesServiceFromFile(QString filename);
    void insert(QString name) override;
    void remove(QString name) override;
    bool contains(QString name) override;
    int listenToChange(std::function<void(FavouritesService::CHANGE_TYPE, QString)>) override;
    void removeListener(int) override;

    void store() override;
    void load() override;
private:
    AutoKeyIntMap<std::function<void(FavouritesService::CHANGE_TYPE, QString)>> listeners;
    std::unordered_set<QString> name_set;
    QString filename;
};


#endif // FAVOURITESSERVICE_H
