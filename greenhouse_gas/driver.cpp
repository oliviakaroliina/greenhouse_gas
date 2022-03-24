#include "driver.hh"

#include <QDebug>
#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <memory>
#include <iostream>

driver::driver(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QObject::connect(&w,&MainWindow::visualizeButtonPressed,this,&driver::createApis);
    errorHandler errorhandler;

    a.exec();

    // Api jutut
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    std::shared_ptr<statfiApi> handler{ std::make_shared<statfiApi>() };
    engine.rootContext()->setContextProperty("networkHandler", handler.get());

    const QUrl url(QStringLiteral("https://pxnet2.stat.fi/PXWeb/api/v1/en/ymp/taulukot/Kokodata.px"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    app.exec();
}

void driver::createApis()
{
    smearApi smear;
    statfiApi statfi;

    QObject::connect(&smear,&smearApi::dataFetched,this,&driver::createDataHandler);
}

void driver::createDataHandler()
{
    dataHandler datahandler;
    QObject::connect(&datahandler,&dataHandler::dataFetchedFromApis,this,&driver::createPlotWindow);
}

void driver::createPlotWindow()
{
    PlotWindow p;
    p.show();
}
