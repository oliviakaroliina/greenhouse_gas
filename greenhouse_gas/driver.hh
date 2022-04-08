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
    // Creates api classes and sends
    // signals to them
    void createApis();

    // Saves the information that Smear data has been collected
    void setSmearDataReady();

    // Saves the information that Statfi data has been collected
    void setStatfiDataReady();

    // Creates datahandler-class and
    // sends signals to them
    void createDataHandler();

    // Creates plotwindow
    void createPlotWindow();

private:
    // Mainwindow class
    MainWindow *mw = nullptr;

    // Creates smear class to make
    // api request to smear
    smearApi* smear = nullptr;

    // Creates statfi class to make
    // api request to statfi
    statfiApi* statfi = nullptr;

    // Creates errorhandler class to
    // handle possible errors
    errorHandler* errorhandler = nullptr;

    // Creates datahandler class to handle
    // data that has been fetched from apis
    dataHandler* datahandler = nullptr;

    // Plotwindow class
    PlotWindow* plotwindow = nullptr;

    bool smearDataReady = false;
    bool statfiDataReady = false;
};

#endif // DRIVER_HH
