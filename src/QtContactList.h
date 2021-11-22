#pragma once
#include <QGuiApplication>
#include <QQuickView>

class QContact :  public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name MEMBER m_name NOTIFY nameChanged)
    Q_PROPERTY(QString number MEMBER m_number NOTIFY numberChanged)
    public:
    /*QContact(QString name, QString number,QObject *parent = 0):QObject(parent){
        this->m_name = name;
        this->m_number = number;
    }
    ~QContact(){}*/
    signals:
    void nameChanged(){

    }
    void numberChanged(){

    }
    private:
    QString m_name;
    QString m_number;
    //QImage
};
