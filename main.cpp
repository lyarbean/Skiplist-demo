//#include <QGuiApplication>
#include <QCoreApplication>
//#include <QQmlApplicationEngine>
#include "skiplist.h"
#include <QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    const QStringList ssl = {"how", "are", "you", "fine", "thank", "apple"};
//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    SkipList sk;
//     for (auto s : ssl) {
//         sk.insert (s);
//         qDebug() << sk();
//         qDebug() <<"--";
//     }
    for (int i = 0; i < 1e4; ++i) {
        sk.insert(QString::number(qrand(), 16));
    }
    qDebug() << sk();
    sk.veto ();
    return app.exec();
}
