#include "Contact.h"
#include "utils.hpp"
#include<QDebug>

SimpleContact::SimpleContact(std::string name, std::string number):name(name),number(number){}

std::string SimpleContact::getName() const{
    return this->name;
}

std::string SimpleContact::getNumber() const{
    return this->number;
}

StarrableContact::StarrableContact(std::string name, std::string number, bool favourite):SimpleContact(name,number), favourite(favourite){}

bool StarrableContact::getFavourite() const{
    return favourite;
}
const char hex_symbols[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
GeneratedPhotoContact::GeneratedPhotoContact(std::string name, std::string number):SimpleContact(name, number){
    int checksum = crc32_checksum(name);
    this->head_type = getNumberBits(checksum,12,13)+1;
    this->color = "#";
    color.push_back(hex_symbols[getNumberBits(checksum,0,2)+8]);
    color.push_back(hex_symbols[getNumberBits(checksum,4,6)+8]);
    color.push_back(hex_symbols[getNumberBits(checksum,7,9)+8]);
}

int GeneratedPhotoContact::getHeadType() const{
    return this->head_type;
}
