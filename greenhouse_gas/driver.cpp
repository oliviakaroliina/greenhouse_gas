#include "driver.hh"

#include <QDebug>
#include <QApplication>

driver::driver(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mw = new MainWindow;
    // Signals that user has made his choices so the api calls can begin
    connect(mw,&MainWindow::visualizeButtonPressed,this,&driver::createApis);

    errorhandler = new errorHandler();

    mw->show();
    a.exec();
}

driver::~driver()
{
    delete errorhandler;
    if (smear != nullptr) {
        delete smear;
    }
    if (statfi != nullptr) {
        delete statfi;
    }
    if (datahandler != nullptr) {
        delete datahandler;
    }
    if (plotwindow != nullptr) {
        delete plotwindow;
    }
}

void driver::createApis()
{
    // Calls the correct api class
    QVector<QString> apis = mw->getApis();
    if (std::find(apis.begin(), apis.end(), "smear") != apis.end()) {
        smear = new smearApi(nullptr, mw);
    }
    if (std::find(apis.begin(), apis.end(), "statfi") != apis.end()) {
        statfi = new statfiApi(nullptr, mw);
    }
    // Signals that data has been colloected so datahandler can be created
    connect(smear,&smearApi::dataCollected,this,&driver::createDataHandler);
}

void driver::createDataHandler()
{
    datahandler = new dataHandler(smear, statfi);
    connect(datahandler,&dataHandler::dataHandled,this,&driver::createPlotWindow);
    datahandler->handleSmearData();
}

void driver::createPlotWindow()
{
    plotwindow = new PlotWindow(nullptr);
    plotwindow->show();
}
