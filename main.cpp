#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "trainmodel.h"
#include "trainfetcher.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Create model and fetcher
    TrainModel trainModel;
    TrainFetcher trainFetcher(&trainModel);  // Fetcher updates model automatically

    // Expose TrainModel to QML
    engine.rootContext()->setContextProperty("trainModel", &trainModel);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Metra2", "Main");

    return app.exec();
}
