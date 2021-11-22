#ifndef CONTACT_H
#define CONTACT_H

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

};
class StarrableContact: virtual public SimpleContact{

};
class GeneratedPhotoContact: virtual public SimpleContact{
};
class Contact: public StarrableContact, public GeneratedPhotoContact{

};

#endif // CONTACT_H
