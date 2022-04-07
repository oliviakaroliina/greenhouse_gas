#include "statfiapi.hh"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

statfiApi::statfiApi(QObject *parent, MainWindow* mw) :
    QObject{ parent }
{
    manager_ = new QNetworkAccessManager(this);
    connect(manager_, &QNetworkAccessManager::finished, this,
            &statfiApi::downloadCompleted);
    mw_ = mw;
    fetch();
}

statfiApi::~statfiApi()
{
    delete manager_;
}

void statfiApi::fetch()
{
    QString url = "https://pxnet2.stat.fi:443/PXWeb/api/v1/en/ymp/taulukot/"
                  "Kokodata.px";
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject outerObject;
    QJsonArray queryArray;

    QJsonObject gasObject;
    gasObject.insert("code", "Tiedot");

    QJsonObject gasSelectionObject;
    gasSelectionObject.insert("filter", "item");

    QJsonArray datasetValuesArray;
    datasetValuesArray.push_back("Khk_yht");
    gasSelectionObject.insert("values", datasetValuesArray);

    gasObject.insert("selection", gasSelectionObject);

    queryArray.push_back(gasObject);


    QJsonObject yearObject;
    yearObject.insert("code", "Vuosi");

    QJsonObject yearSelectionObject;
    yearSelectionObject.insert("filter", "item");

    QJsonArray yearValuesArray;
    yearValuesArray.push_back("2008");
    yearSelectionObject.insert("values", yearValuesArray);

    yearObject.insert("selection", yearSelectionObject);

    queryArray.push_back(yearObject);

    outerObject.insert("query", queryArray);

    qDebug() << outerObject;

    QJsonDocument doc(outerObject);
    QByteArray data = doc.toJson();

    manager_->post(request, data);
}

void statfiApi::downloadCompleted(QNetworkReply *networkReply)
{
    QString response = networkReply->readAll();
    qDebug() << response;
    networkReply->deleteLater();
}
