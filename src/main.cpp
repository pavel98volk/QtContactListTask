#include <QGuiApplication>
#include <QQuickView>
#include <QObject>
#include <iostream>
#include "QContactListModel.h"





int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);
    qmlRegisterType<QContactListModel>("Custom",1,0,"QContactListModel");
    QQuickView view;
    view.setSource(QUrl("qrc:///qml/MainView.qml"));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.show();

    return app.exec();
}
