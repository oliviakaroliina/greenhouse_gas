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
    get_parameters(mw);
    //fetch("2022-01-19T14:00:00.000","2022-01-19T17:00:00.000", "MAX", "KUM_EDDY.av_c_ep");
}

smearApi::~smearApi()
{
    delete manager_;
}

void smearApi::fetch(QString start, QString end, QString aggregation, QString gas_station)
{
    qDebug() << "smearapi fetch";
    QString url_str = "";
    url_str.append("https://smear-backend.rahtiapp.fi/search/timeseries?aggregation=");
    url_str.append(aggregation);
    url_str.append("&interval=");
    url_str.append("60");
    url_str.append("&from=");
    url_str.append(start);
    url_str.append("&to=");
    url_str.append(end);
    url_str.append("&tablevariable=");
    url_str.append(gas_station);
    qDebug() << url_str;
    manager_->get(QNetworkRequest(QUrl(url_str)));
    qDebug() << "?";
}

void smearApi::get_parameters(MainWindow *mw)
{
    qDebug() << mw->getSmearStartDate();
    if (mw->getApis().empty()) {
        qDebug() << "smear ei valittu";
    } else {
        qDebug() << "smear valittu";
    }

    QVector<QString> stations = mw->getMonitoringStations();
    QVector<QString> gases = mw->getGreenhouseGases();
    auto varrio = std::find(stations.begin(), stations.end(), "varrio") != stations.end();
    auto hyytiala = std::find(stations.begin(), stations.end(), "hyytiala") != stations.end();
    auto kumpula = std::find(stations.begin(), stations.end(), "kumpula") != stations.end();
    auto co2 = std::find(gases.begin(), gases.end(), "co2") != gases.end();
    auto so2 = std::find(gases.begin(), gases.end(), "so2") != gases.end();
    auto nox = std::find(gases.begin(), gases.end(), "nox") != gases.end();

    qDebug() << mw->getApis();
    QVector<QString> apis = mw->getApis();
    // Jos smear valittuna nii sit katotaan löytyykö mitä asemia ja kaasuja: saadaan gas_station muuttuja apia varten
    if (std::find(apis.begin(), apis.end(), "smear") != apis.end()) {
        if (varrio and co2) {
            fetch(mw->getSmearStartDate().toString(Qt::ISODate),mw->getSmearEndDate().toString(Qt::ISODate),
                  mw->getDatatype(), "VAR_EDDY.av_c"); }
        qDebug() << mw->getSmearStartDate().toString();
        if (varrio and so2) {
            fetch(mw->getSmearStartDate().toString(Qt::ISODate),mw->getSmearEndDate().toString(Qt::ISODate),
                  mw->getDatatype(), "VAR_META.SO2_1"); }
        if (varrio and nox) {
            fetch(mw->getSmearStartDate().toString(Qt::ISODate),mw->getSmearEndDate().toString(Qt::ISODate),
                  mw->getDatatype(), "VAR_META.NO_1"); }
        if (hyytiala and co2) {
            fetch(mw->getSmearStartDate().toString(Qt::ISODate),mw->getSmearEndDate().toString(Qt::ISODate),
                  mw->getDatatype(), "HYY_META.CO2icos168"); }
        if (hyytiala and so2) {
            fetch(mw->getSmearStartDate().toString(Qt::ISODate),mw->getSmearEndDate().toString(Qt::ISODate),
                  mw->getDatatype(), "HYY_META.SO2168"); }
        if (hyytiala and nox) {
            fetch(mw->getSmearStartDate().toString(Qt::ISODate),mw->getSmearEndDate().toString(Qt::ISODate),
                  mw->getDatatype(), "HYY_META.NO168"); }
        if (kumpula and co2) {
            fetch(mw->getSmearStartDate().toString(Qt::ISODate),mw->getSmearEndDate().toString(Qt::ISODate),
                  mw->getDatatype(), "KUM_EDDY.av_c_ep"); }
        if (kumpula and so2) {
            fetch(mw->getSmearStartDate().toString(Qt::ISODate),mw->getSmearEndDate().toString(Qt::ISODate),
                  mw->getDatatype(), "KUM_META.SO_2"); }
        if (kumpula and nox) {
            fetch(mw->getSmearStartDate().toString(Qt::ISODate),mw->getSmearEndDate().toString(Qt::ISODate),
                  mw->getDatatype(), "KUM_META.NO"); }
    }
    //fetch("2022-01-17T14:00:00.000","2022-01-19T17:00:00.000", "MAX", "KUM_EDDY.av_c_ep");
}

void smearApi::downloadCompleted(QNetworkReply *networkReply)
{
    qDebug() << "smearapi downloadCompleted";
    QString response = networkReply->readAll();
    networkReply->deleteLater();
    qDebug() << response;
    //emit dataFetchedFromSmear();
}
