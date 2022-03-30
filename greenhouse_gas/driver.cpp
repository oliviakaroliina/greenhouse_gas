#include "driver.hh"

#include <QDebug>
#include <QApplication>

driver::driver(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    connect(&w,&MainWindow::visualizeButtonPressed,this,&driver::createApis);

    errorHandler errorhandler;

    w.show();
    a.exec();
}

void driver::createApis()
{
    qDebug() << "createapis";
    smearApi smear;
    statfiApi statfi;

    connect(&smear,&smearApi::dataFetchedFromSmear,this,&driver::createDataHandler);
}

void driver::createDataHandler()
{
    dataHandler datahandler;
    connect(&datahandler,&dataHandler::dataFetchedFromApis,this,&driver::createPlotWindow);
}

void driver::createPlotWindow()
{
    PlotWindow p;
    p.show();
}
