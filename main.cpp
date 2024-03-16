#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include "LogicHandler.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //change toolbar icon
    app.setWindowIcon(QIcon(":/QmlCalculator/Assets/application_icon.ico"));

    //define the class for handling all calculator logic and connect it to qml
    LogicHandler *logicHandler = new LogicHandler(&app);
    qmlRegisterSingletonInstance("local.LogicHandler", 1, 0, "LogicHandler", logicHandler);




    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/QmlCalculator/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
