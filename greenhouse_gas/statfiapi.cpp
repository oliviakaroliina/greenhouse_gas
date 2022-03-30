#include "statfiapi.hh"

statfiApi::statfiApi(QObject *parent) :
    QObject{ parent }
{
    manager_ = new QNetworkAccessManager(this);
    connect(manager_, &QNetworkAccessManager::finished, this,
            &statfiApi::downloadCompleted);
    fetch();
}

statfiApi::~statfiApi()
{
    delete manager_;
}

void statfiApi::fetch()
{
    manager_->get(QNetworkRequest(
                  QUrl("")));
}

void statfiApi::downloadCompleted(QNetworkReply *networkReply)
{
    //QString response = networkReply->readAll();
    networkReply->deleteLater();
    //emit dataFetchedFromStatfi();
}
