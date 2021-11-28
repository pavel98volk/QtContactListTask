#pragma once
#include "FavouritesService.h"

class FavouritesServiceLocalFileImpl: public FavouritesService
{
public:
    FavouritesServiceLocalFileImpl(QString filename);
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
