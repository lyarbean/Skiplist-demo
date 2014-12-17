#include <QGuiApplication>
#include <QQmlApplicationEngine>
// #include <QtDeclarative/QDeclarativeContext>
#include <QtQml>
// #include "skiplistmodel.h"
#include "skiplistitemmodel.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
//     qmlRegisterType<SkipListModel>("SkipListModel", 1, 0, "SkipListModel");
    qmlRegisterType<SkipListListModel>("SkipListItemModel", 1, 0, "SkipListItemModel");
    QQmlApplicationEngine engine;

//    SkipListModel* slm = new SkipListModel();
//    QQmlContext * qdc = engine.rootContext ();
//    qdc->setContextProperty ( "the_model", slm);
    engine.load(QUrl(QStringLiteral("qrc:/gridview.qml")));
//     SkipList sk;
//     for (int i = 0; i < 1e4; ++i) {
//         sk.insert(QString::number(qrand(), 16));
//     }
//     qDebug() << sk();
//     sk.veto ();
    return app.exec();
}
