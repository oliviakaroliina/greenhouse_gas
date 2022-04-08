#ifndef DATAHANDLER_HH
#define DATAHANDLER_HH

#include "smearapi.hh"
#include "statfiapi.hh"
#include "station.hh"

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

    QVector<Station*> getStations();
    void testStationNames();
    void handleSmearData();

public slots:
    void areAllDataHandled();

signals:
    void dataHandled();

private:
    smearApi* smear_ = nullptr;
    statfiApi* statfi_ = nullptr;
    QVector<Station*> stationData = {};
    QVector<QString> stationNames = {};

    void handleStatfiData();
    void getInfo(QString& station, QString& gas, QString& variable);

    bool smearDataHandled = false;
    bool statfiDataHandled = false;

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
};

#endif // DATAHANDLER_HH
