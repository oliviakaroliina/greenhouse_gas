#ifndef DATAHANDLER_HH
#define DATAHANDLER_HH

#include "QObject"

class dataHandler : public QObject
{
    Q_OBJECT
public:
    dataHandler();

signals:
    void dataHandled();
private:
    void handleSmearData();
    void handleStatfiData();
    void areAllDataHandled();

    bool smearDataHandled = false;
    bool statfiDataHandled = false;
};

#endif // DATAHANDLER_HH
