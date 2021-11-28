#include "Contact.h"
#include "utils.h"
#include<QDebug>

SimpleContact::SimpleContact(QString name, QString number):name(name),number(number){}

QString SimpleContact::getName() const{
    return this->name;
}

QString SimpleContact::getNumber() const{
    return this->number;
}


