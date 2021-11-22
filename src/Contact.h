#pragma once
#include <string>

#include <QObject>
class QContactModel :  public QObject
{
    Q_OBJECT
    public:
    QContactModel(QString name, QString number,QObject *parent = 0):QObject(parent){
        this->m_name = name;
        this->m_number = number;
    }
    ~QContactModel() override{};

    Q_PROPERTY(QString name MEMBER m_name NOTIFY nameChanged)
    Q_PROPERTY(QString number MEMBER m_number NOTIFY numberChanged)
    public:
    signals:
    void nameChanged(QString name);
    void numberChanged(QString number);
    private:
    QString m_name;
    QString m_number;
    //QImage
};

class SimpleContact{
    public:
    SimpleContact(std::string name, std::string number);;
    std::string getName()const;
    std::string getNumber()const;
    private:
    std::string name, number;
};
class StarrableContact:virtual public SimpleContact{
    public:
    StarrableContact(std::string name, std::string number, bool favourite);;
    bool getFavourite()const;
private:
    bool favourite;
};


class GeneratedPhotoContact: virtual public SimpleContact{
public:
    GeneratedPhotoContact(std::string name, std::string number);;
    std::string getImageColor()const{return this->color;}
    int getHeadType()const;

private:
    uint8_t head_type;
    std::string color;
};
class Contact: public StarrableContact, public GeneratedPhotoContact{
public:
    Contact(std::string name, std::string number, bool favourite):
        SimpleContact(name, number),
        StarrableContact(name, number, favourite),
        GeneratedPhotoContact(name, number){};
};
