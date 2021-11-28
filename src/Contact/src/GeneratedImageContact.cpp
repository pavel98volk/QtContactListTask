#include "GeneratedImageContact.h"
#include "utils.h"

const char hex_symbols[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
GeneratedImageContact::GeneratedImageContact(QString name, QString number):SimpleContact(name, number){
    int checksum = crc32_checksum(name.toStdString());
    this->head_type = getNumberBits(checksum,12,13)+1;
    this->color = "#";
    color.push_back(hex_symbols[getNumberBits(checksum,0,2)+8]);
    color.push_back(hex_symbols[getNumberBits(checksum,4,6)+8]);
    color.push_back(hex_symbols[getNumberBits(checksum,7,9)+8]);
}

GeneratedImageContact::GeneratedImageContact(const SimpleContact &contact):SimpleContact(contact){
    unsigned int checksum = crc32_checksum(contact.getName().toStdString());
    this->head_type = getNumberBits(checksum,12,13)+1;
    this->color = "#";
    color.push_back(hex_symbols[getNumberBits(checksum,0,2)+8]);
    color.push_back(hex_symbols[getNumberBits(checksum,4,6)+8]);
    color.push_back(hex_symbols[getNumberBits(checksum,7,9)+8]);
}

int GeneratedImageContact::getHeadType() const{
    return this->head_type;
}
