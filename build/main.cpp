#include <QGuiApplication>
#include <QtQuick/QQuickView>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    //QQmlApplicationEngine engine(QUrl::fromLocalFile("qml/main.qml"));
    QQmlApplicationEngine engine;
    engine.load(QUrl("qrc:/qml/main.qml"));

    return app.exec();

//    QQuickView view();
//    QQuickView view;
//    view.setSource(QUrl::fromLocalFile("qml/main.qml"));

//    view.show();
//    return app.exec();
}
