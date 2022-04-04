#ifndef DRIVER_HH
#define DRIVER_HH

#include "plotwindow.h"
#include "smearapi.hh"
#include "statfiapi.hh"
#include "datahandler.hh"
#include "mainwindow.hh"
#include "errorhandler.hh"


class driver : public QObject
{
    Q_OBJECT
public:
    driver(int argc, char *argv[]);
    ~driver();

private slots:
    void createApis();
    void createDataHandler();
    void createPlotWindow();

private:
    MainWindow *mw = nullptr;
    smearApi* smear = nullptr;
    statfiApi* statfi = nullptr;
    errorHandler* errorhandler = nullptr;
    dataHandler* datahandler = nullptr;
    PlotWindow* plotwindow = nullptr;
};

#endif // DRIVER_HH
