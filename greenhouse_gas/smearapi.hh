#ifndef SMEARAPI_HH
#define SMEARAPI_HH

#include <QObject>
#include <QNetworkReply>
#include "mainwindow.hh"

class QNetworkAccessManager;

class smearApi : public QObject
{
    Q_OBJECT

public:
    explicit smearApi(QObject* parent = nullptr, MainWindow* mw = nullptr);
    ~smearApi();

    // Returns a response from get-request to api
    QVector<QString> getResponse();

signals:
    void dataCollected();

private Q_SLOTS:
    void downloadCompleted(QNetworkReply* networkReply);

private:
    // Manages the get-request from api
    QNetworkAccessManager* manager_;

    // Saves the responses to a vector
    QVector<QString> response_ = {};

    // Saves user's choices in mainwindow ui
    MainWindow* mw_ = nullptr;

    // Saves how many selections user has made
    int selections_ = 0;

    // Parameters:
    // - start: the start date
    // - end: the end date
    // - aggregation: type of data (min, max etc.)
    // - gas_station: station where the data is collected from
    // Makes the get request with correct url and
    // fetches data
    void fetch(QString start, QString end, QString aggregation,
               QString gas_station);

    // Gets user's selections from mainwindow
    void get_users_selections();

    // Variables for stations and gasses
    const QString VARRIO = "varrio";
    const QString HYYTIALA = "hyytiala";
    const QString KUMPULA = "kumpula";
    const QString CO2 = "co2";
    const QString SO2 = "so2";
    const QString NOX = "nox";
    const QString VARCO2 = "VAR_EDDY.av_c";
    const QString VARSO2 = "VAR_META.SO2_1";
    const QString VARNOX = "VAR_META.NO_1";
    const QString HYYCO2 = "HYY_META.CO2icos168";
    const QString HYYSO2 = "HYY_META.SO2168";
    const QString HYYNOX = "HYY_META.NO168";
    const QString KUMCO2 = "KUM_EDDY.av_c_ep";
    const QString KUMSO2 = "KUM_META.SO_2";
    const QString KUMNOX = "KUM_META.NO";
};

#endif // NETWORKHANDLER_HH
