#include "statfiapi.hh"

statfiApi::statfiApi(QObject *parent, MainWindow* mw) :
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
    QString url_str = "";
    url_str.append("https://pxnet2.stat.fi/PXWeb/api/v1/en/ymp/taulukot/Kokodata.px");

    manager_->get(QNetworkRequest(
                  QUrl(url_str)));
}

void statfiApi::downloadCompleted(QNetworkReply *networkReply)
{
    //QString response = networkReply->readAll();
    networkReply->deleteLater();
}
