#pragma once
#include <QString>

class SimpleContact{
    public:
    SimpleContact(QString name, QString number);;
    QString getName()const;
    QString getNumber()const;
    private:
    QString name, number;
};
