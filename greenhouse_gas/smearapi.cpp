#include "smearapi.hh"
#include "mainwindow.hh"
#include <QDebug>
#include <iostream>

smearApi::smearApi(QObject *parent, MainWindow *mw) :
    QObject{ parent }
{
    manager_ = new QNetworkAccessManager(this);
    connect(manager_, &QNetworkAccessManager::finished, this,
            &smearApi::downloadCompleted);
    getParameters(mw);
}

smearApi::~smearApi()
{
    delete manager_;
}

QVector<QString> smearApi::getResponse()
{
    return response;
}

void smearApi::fetch(QString start, QString end, QString aggregation,
                     QString gas_station)
{
    QString url_str = "";
    url_str.append("https://smear-backend.rahtiapp.fi/search/timeseries?"
                   "aggregation=");
    url_str.append(aggregation);
    url_str.append("&interval=60");
    url_str.append("&from=");
    url_str.append(start);
    url_str.append("T00:00:00.000");
    url_str.append("&to=");
    url_str.append(end);
    url_str.append("T23:59:59.000");
    url_str.append("&tablevariable=");
    url_str.append(gas_station);

    manager_->get(QNetworkRequest(QUrl(url_str)));
}

void smearApi::getParameters(MainWindow *mw)
{
    QVector<QString> stations = mw->getMonitoringStations();
    QVector<QString> gases = mw->getGreenhouseGases();
    bool varrio = std::find(stations.begin(), stations.end(), VARRIO) !=
                  stations.end();
    bool hyytiala = std::find(stations.begin(), stations.end(), "hyytiala") !=
                    stations.end();
    bool kumpula = std::find(stations.begin(), stations.end(), "kumpula") !=
                   stations.end();
    bool co2 = std::find(gases.begin(), gases.end(), "co2") != gases.end();
    bool so2 = std::find(gases.begin(), gases.end(), "so2") != gases.end();
    bool nox = std::find(gases.begin(), gases.end(), "nox") != gases.end();

    // Finds the correct information related to certain station and gas
    if (varrio and co2) {
        fetch(mw->getSmearStartDate().toString(Qt::ISODate),
              mw->getSmearEndDate().toString(Qt::ISODate),
              mw->getDatatype(), "VAR_EDDY.av_c"); }
    if (varrio and so2) {
        fetch(mw->getSmearStartDate().toString(Qt::ISODate),
              mw->getSmearEndDate().toString(Qt::ISODate),
              mw->getDatatype(), "VAR_META.SO2_1"); }
    if (varrio and nox) {
        fetch(mw->getSmearStartDate().toString(Qt::ISODate),
              mw->getSmearEndDate().toString(Qt::ISODate),
              mw->getDatatype(), "VAR_META.NO_1"); }
    if (hyytiala and co2) {
        fetch(mw->getSmearStartDate().toString(Qt::ISODate),
              mw->getSmearEndDate().toString(Qt::ISODate),
              mw->getDatatype(), "HYY_META.CO2icos168"); }
    if (hyytiala and so2) {
        fetch(mw->getSmearStartDate().toString(Qt::ISODate),
              mw->getSmearEndDate().toString(Qt::ISODate),
              mw->getDatatype(), "HYY_META.SO2168"); }
    if (hyytiala and nox) {
        fetch(mw->getSmearStartDate().toString(Qt::ISODate),
              mw->getSmearEndDate().toString(Qt::ISODate),
              mw->getDatatype(), "HYY_META.NO168"); }
    if (kumpula and co2) {
        fetch(mw->getSmearStartDate().toString(Qt::ISODate),
              mw->getSmearEndDate().toString(Qt::ISODate),
              mw->getDatatype(), "KUM_EDDY.av_c_ep"); }
    if (kumpula and so2) {
        fetch(mw->getSmearStartDate().toString(Qt::ISODate),
              mw->getSmearEndDate().toString(Qt::ISODate),
              mw->getDatatype(), "KUM_META.SO_2"); }
    if (kumpula and nox) {
        fetch(mw->getSmearStartDate().toString(Qt::ISODate),
              mw->getSmearEndDate().toString(Qt::ISODate),
              mw->getDatatype(), "KUM_META.NO"); }
}

void smearApi::downloadCompleted(QNetworkReply *networkReply)
{
    response.push_back(networkReply->readAll());
    qDebug() << response;
    networkReply->deleteLater();
}
