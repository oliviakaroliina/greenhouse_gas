#include "driver.hh"

#include <QDebug>
#include <QApplication>

driver::driver(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mw = new MainWindow;
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
    QVector<QString> apis = mw->getApis();
    if (std::find(apis.begin(), apis.end(), "smear") != apis.end()) {
        smear = new smearApi(nullptr, mw);
    }
    if (std::find(apis.begin(), apis.end(), "statfi") != apis.end()) {
        statfi = new statfiApi(nullptr, mw);
    }
    connect(smear,&smearApi::dataCollected,this,&driver::createDataHandler);
}

void driver::createDataHandler()
{
    datahandler = new dataHandler(smear, statfi);
    connect(datahandler,&dataHandler::dataHandled,this,&driver::createPlotWindow);
}

void driver::createPlotWindow()
{
    plotwindow = new PlotWindow(nullptr);
    plotwindow->show();
}
