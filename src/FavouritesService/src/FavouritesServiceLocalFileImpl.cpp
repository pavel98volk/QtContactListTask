#include "FavouritesServiceLocalFileImpl.h"
#include <QFile>
#include <fstream>



FavouritesServiceLocalFileImpl::FavouritesServiceLocalFileImpl(QString filename)
{
    this->filename = filename;
}

void FavouritesServiceLocalFileImpl::insert(QString name)
{
    name_set.insert(name);
    this->store();
    for(const auto& listener: listeners){
        listener.second(CHANGE_TYPE::Insert,name);
    }
}
void FavouritesServiceLocalFileImpl::remove(QString name)
{
    name_set.erase(name);
    this->store();
    for(const auto& listener: listeners){
        listener.second(CHANGE_TYPE::Remove,name);
    }
}
bool FavouritesServiceLocalFileImpl::contains(QString name)
{
    return name_set.find(name) != name_set.end();
}

int FavouritesServiceLocalFileImpl::listenToChange(std::function<void(FavouritesServiceLocalFileImpl::CHANGE_TYPE, QString)>listener)
{
    int listener_id = this->listeners.insert_genkey(listener);
    return listener_id;
}

void FavouritesServiceLocalFileImpl::removeListener(int listener_id)
{
    this->listeners.erase(listener_id);
}
void FavouritesServiceLocalFileImpl::store()
{
    //1. open file and initialize filestream
    QFile file(this->filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text ))
        return;
    QTextStream out(&file);
    for(const QString& name : name_set){
        out << name << Qt::endl;
    }
}
void FavouritesServiceLocalFileImpl::load()
{
    //1. open file and initialize filestream
    QFile file(this->filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    name_set.clear();
    QTextStream in(&file);
    while(!in.atEnd()){
        name_set.insert(in.readLine());
    }
    for(const auto& listener: listeners){
        listener.second(CHANGE_TYPE::UpdateAll,QString());
    }
}
