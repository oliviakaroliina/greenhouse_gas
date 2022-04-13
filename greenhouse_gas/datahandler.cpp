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
        // Transform the data from smear to Json format
        QJsonDocument doc = QJsonDocument::fromJson(smearResponse.at(i).toUtf8());
        QJsonObject root = doc.object();
        QJsonArray columns = root[COLUMNS].toArray();
        // Save the data to array
        QJsonArray data = root[DATA].toArray();

        // Extract variable and based on that get station name and gas type.
        QString variable = columns[valueLocation].toString();
        QString stationName = "";
        QString gas = "";
        getInfo(stationName, gas, variable);

        for(int k = 0; k < data.size(); k++) {
            QJsonObject values = data[k].toObject();
            // The value of data from one measurement
            QJsonValue dataValue = values.value(QString(variable));
            // If there are no stations yet, create a new one and insert values
            // Ignore null and zero values
            if(stationData.size() == 0 and !dataValue.isNull()
                    and dataValue != 0) {
                Station* station = new Station(stationName);
                stationData.push_back(station);
                stationNames.push_back(stationName);
                station->insertValues(dataValue.toDouble(), gas);
             } else {
                QVector<QString>::iterator it = std::find(stationNames.begin(), stationNames.end(), stationName);
                // If there are stations and a station is already saved, insert more data for it
                if(it != stationNames.end() and !dataValue.isNull()
                        and dataValue != 0) {
                    for(int j = 0; j < stationData.size(); j++) {
                        if(stationData.at(j)->getName() == stationName) {
                            stationData.at(j)->insertValues(dataValue.toDouble(), gas);
                            break;
                        }
                    }
                // Else create a new station and insert data
                } else {
                    if(!dataValue.isNull() and dataValue != 0) {
                        Station* station = new Station(stationName);
                        stationData.push_back(station);
                        stationNames.push_back(stationName);
                        station->insertValues(dataValue.toDouble(), gas);
                    }
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

    // Transform the data from smear to Json format
    for(int i = 0; i < statfiResponse.size(); i++) {
        QJsonDocument doc = QJsonDocument::fromJson(statfiResponse.at(i).toUtf8());
        QJsonObject root = doc.object();
        QJsonObject dimension = root[DIMENSION].toObject();

        // Get the type of dataset that was wanted
        QJsonObject tiedot = dimension[INFORMATION].toObject();
        QJsonObject category = tiedot[CATEGORY].toObject();
        QJsonObject index = category[INDEX].toObject();
        QJsonValue value = index.keys().at(valueLocation);
        QString datasetType = value.toString();

        // Get the years
        QJsonObject vuosi = dimension[YEAR].toObject();
        QJsonObject categryYear = vuosi[CATEGORY].toObject();
        QJsonObject indexYear = categryYear[INDEX].toObject();
        QVector<double> years;
        for(int j = 0; j < indexYear.keys().size(); j++) {
            QJsonValue yeats = indexYear.keys().at(j);
            QString strYears = yeats.toString();
            double yearDouble = strYears.toDouble();
            years.push_back(yearDouble);
        }

        // Get the values from each year
        QVector<double> values;
        QJsonArray valuesArray = root[VALUE].toArray();
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

