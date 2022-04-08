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
    getUsersSelections();
}

statfiApi::~statfiApi()
{
    delete manager_;
}

QVector<QString> statfiApi::getResponse()
{
    return response_;
}

void statfiApi::fetch(QString start, QString end, QString coType)
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
    datasetValuesArray.push_back(coType);
    gasSelectionObject.insert("values", datasetValuesArray);

    gasObject.insert("selection", gasSelectionObject);

    queryArray.push_back(gasObject);

    QJsonObject yearObject;
    yearObject.insert("code", "Vuosi");

    QJsonObject yearSelectionObject;
    yearSelectionObject.insert("filter", "item");

    QJsonArray yearValuesArray;
    int startInt = start.toInt();
    int endInt = end.toInt();

    if (endInt - startInt < 2) {
        yearValuesArray.push_back(start);
        yearValuesArray.push_back(end);
    }

    else if (endInt - startInt < 1) {
        yearValuesArray.push_back(start);
    }
    else {
        int years = endInt - startInt;
        int n = 0;
        int addYear = 0;
        while (n < years) {
            addYear = startInt + n;
            yearValuesArray.push_back(addYear);
        }
    }
    //yearValuesArray.push_back("2008");
    yearSelectionObject.insert("values", yearValuesArray);

    yearObject.insert("selection", yearSelectionObject);
    queryArray.push_back(yearObject);
    outerObject.insert("query", queryArray);

    QJsonDocument doc(outerObject);
    QByteArray data = doc.toJson();
    qDebug() << outerObject;
    manager_->post(request, data);
}

void statfiApi::getUsersSelections()
{
    QVector<QString> coTypes = mw_->getDatasets();

    bool in_tonnes = std::find(coTypes.begin(), coTypes.end(), IN_TONNES) != coTypes.end();
    bool intensity = std::find(coTypes.begin(), coTypes.end(), INTENSITY) != coTypes.end();
    bool intensity_indexed = std::find(coTypes.begin(), coTypes.end(), INTENSITY_INDEXED) != coTypes.end();
    bool indexed = std::find(coTypes.begin(), coTypes.end(), INDEXED) != coTypes.end();

    QString startDate = QString::number(mw_->getStatfiStartYear());
    QString endDate = QString::number(mw_->getStatfiEndYear());

    startDate = "2008";
    endDate = "2009";
    // CO2 emissions in 1000kgs
    if (in_tonnes) {
        fetch(startDate, endDate, API_IN_TONNES);
        selections_++;
    }

    // CO2 emissions indexed
    if (intensity) {
        fetch(startDate, endDate, API_INTENSITY);
        selections_++;
    }

    // CO2 emissions intensity, indexed
    if (intensity_indexed) {
        fetch(startDate, endDate, API_INTENSITY_INDEXED);
        selections_++;
    }

    // CO2 emissions indexed
    if (indexed) {
        fetch(startDate, endDate, API_INDEXED);
        selections_++;
    }

}

void statfiApi::downloadCompleted(QNetworkReply *networkReply)
{
    response_.push_back(networkReply->readAll());
    qDebug() << "response";
    qDebug() << response_;
    networkReply->deleteLater();

    if (response_.size() == selections_) {
        emit dataCollected();
    }

}
