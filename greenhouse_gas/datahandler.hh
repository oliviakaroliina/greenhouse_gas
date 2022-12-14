#ifndef DATAHANDLER_HH
#define DATAHANDLER_HH

#include "smearapi.hh"
#include "statfiapi.hh"
#include "station.hh"
#include "history.hh"

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDateTime>

class dataHandler : public QObject
{
    Q_OBJECT
public:
    dataHandler(smearApi* smear = nullptr, statfiApi* statfi = nullptr);

    // Handles the data gotten from smearApi and statfiApi
    void handleSmearData();
    void handleStatfiData();

    // Returns a vector that holds information from each station
    QVector<Station*> getStations();
    // Returns a vector that holds information from each data type from statfi
    QVector<History*> getHistorical();

    // Returns the start and end dates from smear
    QString getStartDate();
    QString getEndDate();

public slots:
    void areAllDataHandled();

signals:
    void dataHandled();

private:
    // Fetched data from smear and statfi
    smearApi* smear_ = nullptr;
    statfiApi* statfi_ = nullptr;

    // Vecotrs for saving data
    QVector<Station*> stationData = {};
    QVector<History*> historicalData = {};
    QVector<QString> stationNames = {};

    // Gets station name and gastype based on variable gotten from the data
    void getInfo(QString& station, QString& gas, QString& variable);

    // Variables to tell if data has been handled
    bool smearDataHandled = false;
    bool statfiDataHandled = false;

    // Variables
    const QString VARRIO = "Varrio";
    const QString HYYTIALA = "Hyytiala";
    const QString KUMPULA = "Kumpula";

    const QString CO2 = "CO2";
    const QString SO2 = "SO2";
    const QString NOX = "NOx";

    const QString VARRIOCO2 = "VAR_EDDY.av_c";
    const QString VARRIOSO2 = "VAR_META.SO2_1";
    const QString VARRIONO = "VAR_META.NO_1";

    const QString HYYTIALACO2 = "HYY_META.CO2icos168";
    const QString HYYTIALASO2 = "HYY_META.SO2168";
    const QString HYYTIALANO = "HYY_META.NO168";

    const QString KUMPULACO2 = "KUM_EDDY.av_c_ep";
    const QString KUMPULASO2 = "KUM_META.SO_2";
    const QString KUMPULANO = "KUM_META.NO";

    const QString COLUMNS = "columns";
    const QString DATA = "data";
    const QString SAMPTIME = "samptime";
    const QString DIMENSION = "dimension";
    const QString INFORMATION = "Tiedot";
    const QString CATEGORY = "category";
    const QString INDEX = "index";
    const QString YEAR = "Vuosi";
    const QString VALUE = "value";

    const int valueLocation = 0;
};

#endif // DATAHANDLER_HH
