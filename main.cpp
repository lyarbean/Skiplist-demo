#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "skiplistmodel.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<SkipListModel>("SkipListModel", 1, 0, "SkipListModel");
     
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

//     SkipList sk;
//     for (int i = 0; i < 1e4; ++i) {
//         sk.insert(QString::number(qrand(), 16));
//     }
//     qDebug() << sk();
//     sk.veto ();
    return app.exec();
}
