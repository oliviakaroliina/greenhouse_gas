#ifndef DATAHANDLER_HH
#define DATAHANDLER_HH

#include "QObject"


class dataHandler : public QObject
{
    Q_OBJECT
public:
    dataHandler();

signals:
    void dataFetchedFromApis();
private:
    void fetchDataFromApis();
};

#endif // DATAHANDLER_HH
