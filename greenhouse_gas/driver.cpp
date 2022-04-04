#include "driver.hh"

#include <QDebug>
#include <QApplication>

driver::driver(int argc, char *argv[])
{
    QApplication a(argc, argv);
    w = new MainWindow;
    connect(w,&MainWindow::visualizeButtonPressed,this,&driver::createApis);

    errorHandler errorhandler;

    w->show();
    a.exec();
}

driver::~driver()
{
    if (smear != nullptr) {
        delete smear;
    }
    if (statfi != nullptr) {
        delete statfi;
    }
}

void driver::createApis()
{
    QVector<QString> apis = w->getApis();
    if (std::find(apis.begin(), apis.end(), "smear") != apis.end()) {
        smear = new smearApi(nullptr, w);
        //connect(smear,&smearApi::dataFetchedFromSmear,this,&driver::createDataHandler);
    }
    if (std::find(apis.begin(), apis.end(), "statfi") != apis.end()) {
        statfi = new statfiApi(nullptr);
    }
    createDataHandler();

}

void driver::createDataHandler()
{
    dataHandler datahandler;
    connect(&datahandler,&dataHandler::dataHandled,this,&driver::createPlotWindow);
}

void driver::createPlotWindow()
{
    PlotWindow p;
    p.show();
}
