#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDir>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // set working directory to the executable path
    QString workingPath = QGuiApplication::applicationDirPath();
    QDir::setCurrent(workingPath);

    QQmlApplicationEngine engine;
    engine.addImportPath("../plugins/"); 
    // const QUrl url(u"qrc:/qt/qml/demo/Main.qml"_qs);
    const QUrl url(u"qrc:/qt/qml/Extra/Main.qml"_qs);

    QObject::connect(
            &engine,
            &QQmlApplicationEngine::objectCreated,
            &app,
            [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            },
            Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
