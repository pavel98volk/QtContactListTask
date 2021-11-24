#include "FavouritesService.h"
#include <fstream>



FavouritesServiceFromFile::FavouritesServiceFromFile(std::string filename)
{
    this->filename = filename;
}

void FavouritesServiceFromFile::insert(std::string name)
{
    name_set.insert(name);
}
void FavouritesServiceFromFile::remove(std::string name)
{
   name_set.erase(name);
}
bool FavouritesServiceFromFile::contains(std::string name)
{
    return name_set.find(name) != name_set.end();
}
void FavouritesServiceFromFile::store()
{
    std::ofstream out;
    out.open(this->filename);
    if(!out.is_open()){
        return; // or throw,
    }
    name_set.clear();
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
    name_set.clear();
    std::string line_buffer;
    while(std::getline(in, line_buffer)){
        if (line_buffer.find(",") != std::string::npos) {
            if(line_buffer != ""){
                name_set.insert(line_buffer);
            }
        }
    }
    return;
}
