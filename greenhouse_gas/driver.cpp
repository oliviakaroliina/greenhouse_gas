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

void driver::createApis()
{
    qDebug() << "createapis";
    smearApi* smear = new smearApi(nullptr, w);
    connect(smear,&smearApi::dataFetchedFromSmear,this,&driver::createDataHandler);

    statfiApi statfi;

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
