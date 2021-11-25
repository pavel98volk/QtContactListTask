#ifndef FAVOURITESSERVICE_H
#define FAVOURITESSERVICE_H
#include <string>
#include <unordered_set>
#include "utils.h"

class FavouritesService
{
public:
    virtual void insert(std::string name) = 0;
    virtual void remove(std::string name) = 0;
    virtual bool contains(std::string name) = 0;
    enum CHANGE_TYPE {Insert, Remove, UpdateAll};
    virtual int listenToChange(std::function<void(FavouritesService::CHANGE_TYPE, std::string)>) = 0;
    virtual void removeListener(int) = 0;

    virtual void store() = 0;
    virtual void load() = 0;
};
class FavouritesServiceFromFile: public FavouritesService
{
public:
    FavouritesServiceFromFile(std::string filename);
    void insert(std::string name) override;
    void remove(std::string name) override;
    bool contains(std::string name) override;
    int listenToChange(std::function<void(FavouritesService::CHANGE_TYPE, std::string)>) override;
    void removeListener(int) override;

    void store() override;
    void load() override;
private:
    AutoKeyIntMap<std::function<void(FavouritesService::CHANGE_TYPE, std::string)>> listeners;
    std::unordered_set<std::string> name_set;
    std::string filename;
};


#endif // FAVOURITESSERVICE_H
