#include "FavouritesService.h"
#include <fstream>



FavouritesServiceFromFile::FavouritesServiceFromFile(std::string filename)
{
    this->filename = filename;
}

void FavouritesServiceFromFile::insert(std::string name)
{
    name_set.insert(name);
    this->store();
    for(const auto& listener: listeners){
        listener.second(CHANGE_TYPE::Insert,name);
    }
}
void FavouritesServiceFromFile::remove(std::string name)
{
    name_set.erase(name);
    this->store();
    for(const auto& listener: listeners){
        listener.second(CHANGE_TYPE::Remove,name);
    }
}
bool FavouritesServiceFromFile::contains(std::string name)
{
    return name_set.find(name) != name_set.end();
}

int FavouritesServiceFromFile::listenToChange(std::function<void(FavouritesService::CHANGE_TYPE, std::string)>listener)
{
    int listener_id = this->listeners.insert_genkey(listener);
    return listener_id;
}

void FavouritesServiceFromFile::removeListener(int listener_id)
{
    this->listeners.erase(listener_id);
}
void FavouritesServiceFromFile::store()
{
    std::ofstream out;
    out.open(this->filename);
    if(!out.is_open()){
        return; // or throw,
    }
    std::string line_buffer;
    for(const std::string& name : name_set) {
        out << name << std::endl;
    }
    return;
}
void FavouritesServiceFromFile::load()
{
    std::ifstream in;
    in.open(this->filename);
    if(!in.is_open()){
        return; // or throw,
    }
    for(const auto& listener: listeners){
        listener.second(CHANGE_TYPE::UpdateAll,std::string());
    }
    name_set.clear();
    std::string line_buffer;
    while(std::getline(in, line_buffer)){
        //if (line_buffer.find(",") != std::string::npos) {
            if(line_buffer != ""){
                name_set.insert(line_buffer);
            }
        //}
    }
    return;
}
