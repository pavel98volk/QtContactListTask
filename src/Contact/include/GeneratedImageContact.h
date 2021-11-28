#pragma once
#include "SimpleContact.h"
#include <QString>

class GeneratedImageContact: virtual public SimpleContact{
public:
    GeneratedImageContact(QString name, QString number);
    GeneratedImageContact(const SimpleContact& contact);
    QString getImageColor()const{return this->color;}
    int getHeadType()const;

private:
    uint8_t head_type;
    QString color;
};
