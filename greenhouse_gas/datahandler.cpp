#include "datahandler.hh"

dataHandler::dataHandler(smearApi *smear, statfiApi *statfi)
{
    smear_ = smear;
    statfi_ = statfi;

    handleSmearData();
}

void dataHandler::handleSmearData()
{
    qDebug() << "handle smear data";
    QVector<QString> response = smear_->getResponse();

    for(int i = 0; i < response.size(); i++) {
        QJsonDocument doc = QJsonDocument::fromJson(response.at(i).toUtf8());
        QJsonObject root = doc.object();
        QJsonArray columns = root["columns"].toArray();
        QJsonArray data = root["data"].toArray();

        QString variable = columns[0].toString();
        QString stationName = "";
        QString gas = "";
        getInfo(stationName, gas, variable);
        //QString dateString = "";
        //double value = 0;
        qDebug() << stationName;

        for(int k = 0; k < data.size(); k++) {
            QJsonObject values = data[k].toObject();
            QJsonValue date = values.value(QString("samptime"));
            //dateString = date.toString();
            QJsonValue subval2 = values.value(QString(variable));
            //value = subval2.toDouble();
            if(stationData.size() == 0) {
                Station* station = new Station(stationName, gas);
                //qDebug() << station->getName();
                stationData.push_back(station);
                station->insertValues(date.toString(), subval2.toDouble(), gas);
            } else {
                for(int j = 0; j < stationData.size(); j++) {
                    //qDebug() << j;
                    if(stationData.at(j)->getName() == stationName) {
                        //qDebug() << stationData.at(j)->getName();
                        stationData.at(j)->insertValues(date.toString(), subval2.toDouble(), gas);
                    } else {
                        Station* station = new Station(stationName, gas);
                        //qDebug() << station->getName();
                        stationData.push_back(station);
                        station->insertValues(date.toString(), subval2.toDouble(), gas);
                    }
                }
            }
        }
    }
    smearDataHandled = true;
    //statfiDataHandled = true;
    //areAllDataHandled();
}

void dataHandler::handleStatfiData()
{
    statfiDataHandled = true;
    areAllDataHandled();
}

void dataHandler::areAllDataHandled()
{
    if(smearDataHandled and statfiDataHandled) {
        qDebug() << "moikku";
        emit dataHandled();
        qDebug() << "vaikku";
    }
}

void dataHandler::getInfo(QString &station, QString &gas, QString &variable)
{
    if(variable == VARRIOCO2) {
        station = VARRIO;
        gas = CO2;
    } else if(variable == VARRIOSO2) {
        station = VARRIO;
        gas = SO2;
    } else if(variable == VARRIONO) {
        station = VARRIO;
        gas = NOX;
    } else if(variable == HYYTIALACO2) {
        station = HYYTIALA;
        gas = CO2;
    } else if(variable == HYYTIALASO2) {
        station = HYYTIALA;
        gas = SO2;
    } else if(variable == HYYTIALANO) {
        station = HYYTIALA;
        gas = NOX;
    } else if(variable == KUMPULACO2) {
        station = KUMPULA;
        gas = CO2;
    } else if(variable == KUMPULASO2) {
        station = KUMPULA;
        gas = SO2;
    } else {
        station = KUMPULA;
        gas = NOX;
    }
}

QVector<Station*> dataHandler::getStations()
{
    return stationData;
}
