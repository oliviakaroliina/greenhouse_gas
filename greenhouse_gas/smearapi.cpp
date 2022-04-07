#include "smearapi.hh"
#include "mainwindow.hh"
#include <QDebug>
#include <iostream>
#include <QTime>

smearApi::smearApi(QObject *parent, MainWindow *mw) :
    QObject{ parent }
{
    manager_ = new QNetworkAccessManager(this);
    connect(manager_, &QNetworkAccessManager::finished, this,
            &smearApi::downloadCompleted);
    mw_ = mw;
    get_users_selections();
}

smearApi::~smearApi()
{
    delete manager_;
}

QVector<QString> smearApi::getResponse()
{
    return response_;
}

void smearApi::fetch(QString start, QString end, QString aggregation,
                     QString gas_station)
{
    // Creating the url
    QString url = "";
    url.append("https://smear-backend.rahtiapp.fi/search/timeseries?"
                   "aggregation=");
    url.append(aggregation);
    url.append("&interval=60");
    url.append("&from=");
    url.append(start);
    url.append("T00:00:00.000");
    url.append("&to=");
    url.append(end);

    // Check if the end date is today
    if (QDate::currentDate() == mw_->getSmearEndDate())
    {
        url.append("T");
        QTime currentTime = QTime::currentTime();
        QString time = currentTime.toString("hh:mm:ss.zzz");
        url.append(time);
    }
    else {
        // If the end date is not today, the time
        // will be the end of the end date
        url.append("T23:59:59.000");
    }
    url.append("&tablevariable=");
    url.append(gas_station);

    manager_->get(QNetworkRequest(QUrl(url)));
}

void smearApi::get_users_selections()
{
    QVector<QString> stations = mw_->getMonitoringStations();
    QVector<QString> gases = mw_->getGreenhouseGases();

    // Checking which stations and gasses user has chosen
    bool varrio = std::find(stations.begin(), stations.end(), VARRIO) !=
                  stations.end();
    bool hyytiala = std::find(stations.begin(), stations.end(), HYYTIALA) !=
                    stations.end();
    bool kumpula = std::find(stations.begin(), stations.end(), KUMPULA) !=
                   stations.end();
    bool co2 = std::find(gases.begin(), gases.end(), CO2) != gases.end();
    bool so2 = std::find(gases.begin(), gases.end(), SO2) != gases.end();
    bool nox = std::find(gases.begin(), gases.end(), NOX) != gases.end();

    QString start_date = mw_->getSmearStartDate().toString(Qt::ISODate);
    QString end_date = mw_->getSmearEndDate().toString(Qt::ISODate);
    QString datatype = mw_->getDatatype();

    // Finds the correct information related to certain station and gas
    if (varrio and co2) {
        fetch(start_date, end_date, datatype, VARCO2);
        selections_++;
    }
    if (varrio and so2) {
        fetch(start_date, end_date, datatype, VARSO2);
        selections_++;
    }
    if (varrio and nox) {
        fetch(start_date, end_date, datatype, VARNOX);
        selections_++;
    }
    if (hyytiala and co2) {
        fetch(start_date, end_date, datatype, HYYCO2);
        selections_++;
    }
    if (hyytiala and so2) {
        fetch(start_date, end_date, datatype, HYYSO2);
        selections_++;
    }
    if (hyytiala and nox) {
        fetch(start_date, end_date, datatype, HYYNOX);
        selections_++;
    }
    if (kumpula and co2) {
        fetch(start_date, end_date, datatype, KUMCO2);
        selections_++;
    }
    if (kumpula and so2) {
        fetch(start_date, end_date, datatype, KUMSO2);
        selections_++;
    }
    if (kumpula and nox) {
        fetch(start_date, end_date, datatype, KUMNOX);
        selections_++;
    }
}

void smearApi::downloadCompleted(QNetworkReply *networkReply)
{
    response_.push_back(networkReply->readAll());
    networkReply->deleteLater();

    if(response_.size() == selections_) {
        emit dataCollected();
    }
}
