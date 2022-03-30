#include "smearapi.hh"
#include <QDebug>

smearApi::smearApi(QObject *parent) :
    QObject{ parent }
{
    manager_ = new QNetworkAccessManager(this);
    connect(manager_, &QNetworkAccessManager::finished, this,
            &smearApi::downloadCompleted);
    fetch();
}

smearApi::~smearApi()
{
    delete manager_;
}

void smearApi::fetch()
{
    manager_->get(QNetworkRequest(
                  QUrl("https://smear-backend.rahtiapp.fi/search/station")));
}

void smearApi::downloadCompleted(QNetworkReply *networkReply)
{
    qDebug() << "downloadCompleted slottiin päästy";
    QString response = networkReply->readAll();
    networkReply->deleteLater();
    qDebug() << response;
    //emit dataFetchedFromSmear();
}
