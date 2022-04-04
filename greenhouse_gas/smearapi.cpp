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
    getParameters();
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
    else
    {
        // If the end date is not today, the time will be the end of the end
        // date
        url.append("T23:59:59.000");
    }

    url.append("&tablevariable=");
    url.append(gas_station);

    manager_->get(QNetworkRequest(QUrl(url)));
}

void smearApi::getParameters()
{
    QVector<QString> stations = mw_->getMonitoringStations();
    QVector<QString> gases = mw_->getGreenhouseGases();

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
        fetch(mw_->getSmearStartDate().toString(Qt::ISODate),
              mw_->getSmearEndDate().toString(Qt::ISODate),
              mw_->getDatatype(), "VAR_EDDY.av_c"); }
    if (varrio and so2) {
        fetch(mw_->getSmearStartDate().toString(Qt::ISODate),
              mw_->getSmearEndDate().toString(Qt::ISODate),
              mw_->getDatatype(), "VAR_META.SO2_1"); }
    if (varrio and nox) {
        fetch(mw_->getSmearStartDate().toString(Qt::ISODate),
              mw_->getSmearEndDate().toString(Qt::ISODate),
              mw_->getDatatype(), "VAR_META.NO_1"); }
    if (hyytiala and co2) {
        fetch(mw_->getSmearStartDate().toString(Qt::ISODate),
              mw_->getSmearEndDate().toString(Qt::ISODate),
              mw_->getDatatype(), "HYY_META.CO2icos168"); }
    if (hyytiala and so2) {
        fetch(mw_->getSmearStartDate().toString(Qt::ISODate),
              mw_->getSmearEndDate().toString(Qt::ISODate),
              mw_->getDatatype(), "HYY_META.SO2168"); }
    if (hyytiala and nox) {
        fetch(mw_->getSmearStartDate().toString(Qt::ISODate),
              mw_->getSmearEndDate().toString(Qt::ISODate),
              mw_->getDatatype(), "HYY_META.NO168"); }
    if (kumpula and co2) {
        fetch(mw_->getSmearStartDate().toString(Qt::ISODate),
              mw_->getSmearEndDate().toString(Qt::ISODate),
              mw_->getDatatype(), "KUM_EDDY.av_c_ep"); }
    if (kumpula and so2) {
        fetch(mw_->getSmearStartDate().toString(Qt::ISODate),
              mw_->getSmearEndDate().toString(Qt::ISODate),
              mw_->getDatatype(), "KUM_META.SO_2"); }
    if (kumpula and nox) {
        fetch(mw_->getSmearStartDate().toString(Qt::ISODate),
              mw_->getSmearEndDate().toString(Qt::ISODate),
              mw_->getDatatype(), "KUM_META.NO"); }
}

void smearApi::downloadCompleted(QNetworkReply *networkReply)
{
    response_.push_back(networkReply->readAll());
    qDebug() << response_;
    networkReply->deleteLater();
}
