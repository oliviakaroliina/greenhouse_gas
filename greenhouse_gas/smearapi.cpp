#include "smearapi.hh"
#include <QDebug>
#include <QDateTime>

smearApi::smearApi(QObject *parent) :
    QObject{ parent }
{
    manager_ = new QNetworkAccessManager(this);
    connect(manager_, &QNetworkAccessManager::finished, this,
            &smearApi::downloadCompleted);
    fetch("2022-01-19T14:00:00.000","2022-01-19T17:00:00.000", "MAX", "KUM_EDDY.av_c_ep");
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
    manager_->get(QNetworkRequest(
                  QUrl(url_str)));
}

void smearApi::downloadCompleted(QNetworkReply *networkReply)
{
    qDebug() << "smearapi downloadCompleted";
    QString response = networkReply->readAll();
    networkReply->deleteLater();
    qDebug() << response;
    //emit dataFetchedFromSmear();
}
