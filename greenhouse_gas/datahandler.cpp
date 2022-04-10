#include "datahandler.hh"

dataHandler::dataHandler(smearApi *smear, statfiApi *statfi)
{
    smear_ = smear;
    statfi_ = statfi;
}

void dataHandler::handleSmearData()
{
    QVector<QString> smearResponse = smear_->getResponse();

    for(int i = 0; i < smearResponse.size(); i++) {
        QJsonDocument doc = QJsonDocument::fromJson(smearResponse.at(i).toUtf8());
        QJsonObject root = doc.object();
        QJsonArray columns = root["columns"].toArray();
        QJsonArray data = root["data"].toArray();

        QString variable = columns[0].toString();
        QString stationName = "";
        QString gas = "";
        getInfo(stationName, gas, variable);

        for(int k = 0; k < data.size(); k++) {
            QJsonObject values = data[k].toObject();
            QJsonValue date = values.value(QString("samptime")); // kellonaika
            QJsonValue dataValue = values.value(QString(variable)); // datan arvo
            if(stationData.size() == 0) {
                Station* station = new Station(stationName);
                stationData.push_back(station);
                stationNames.push_back(stationName);
                station->insertValues(dataValue.toDouble(), gas);
             } else {
                QVector<QString>::iterator it = std::find(stationNames.begin(), stationNames.end(), stationName);
                if(it != stationNames.end()) { // löytyy
                    for(int j = 0; j < stationData.size(); j++) {
                        if(stationData.at(j)->getName() == stationName) {
                            stationData.at(j)->insertValues(dataValue.toDouble(), gas);
                            break;
                        }
                    }
                } else { // ei löydy
                    Station* station = new Station(stationName);
                    stationData.push_back(station);
                    stationNames.push_back(stationName);
                    station->insertValues(dataValue.toDouble(), gas);
                }
            }
        }
    }
    smearDataHandled = true;
    areAllDataHandled();
}

void dataHandler::handleStatfiData()
{
    QVector<QString> statfiResponse = statfi_->getResponse();

    for(int i = 0; i < statfiResponse.size(); i++) {
        QJsonDocument doc = QJsonDocument::fromJson(statfiResponse.at(i).toUtf8());
        QJsonObject root = doc.object();
        QJsonObject dimension = root["dimension"].toObject();

        QJsonObject tiedot = dimension["Tiedot"].toObject();
        QJsonObject category = tiedot["category"].toObject();
        QJsonObject index = category["index"].toObject();
        QJsonValue value = index.keys().at(0);
        QString datasetType = value.toString();

        QJsonObject vuosi = dimension["Vuosi"].toObject();
        QJsonObject categryYear = vuosi["category"].toObject();
        QJsonObject indexYear = categryYear["index"].toObject();
        QVector<double> years;
        for(int j = 0; j < indexYear.keys().size(); j++) {
            QJsonValue yeats = indexYear.keys().at(j);
            QString strYears = yeats.toString();
            double yearDouble = strYears.toDouble();
            years.push_back(yearDouble);
        }
        // MUISTA STATFIAPIIN while (n <= years), muuten ei ota vipaa vuotta
        QVector<double> values;
        QJsonArray valuesArray = root["value"].toArray();
        for(int k = 0; k < valuesArray.size(); k++) {
            values.push_back(valuesArray.at(k).toDouble());
        }
        History* history = new History(datasetType, years, values);
        historicalData.push_back(history);
    }
    statfiDataHandled = true;
    areAllDataHandled();
}

void dataHandler::areAllDataHandled()
{
    if(smearDataHandled and statfiDataHandled) {
        emit dataHandled();
    }
    if(smearDataHandled and statfi_ == nullptr) {
        emit dataHandled();
    }
    if(statfiDataHandled and smear_ == nullptr) {
        emit dataHandled();
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

QString dataHandler::getStartDate()
{
    return smear_->getStartDate();
}

QString dataHandler::getEndDate()
{
    return smear_->getEndDate();
}

QVector<Station*> dataHandler::getStations()
{
    return stationData;
}

QVector<History*> dataHandler::getHistorical()
{
    return historicalData;
}

