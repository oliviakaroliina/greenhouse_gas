#include "station.hh"

Station::Station(QString name)
{
    name_ = name;
}

QString Station::getName()
{
    return name_;
}


void Station::insertValues(double value, QString gasType)
{
    if(gasType == CO2) {
        if(CO2x_.size() == 0) {
            CO2x_.push_back(1);
        } else {
            double previous = CO2x_.last();
            CO2x_.push_back(previous + 1);
        }
        CO2y_.push_back(value);
    } else if(gasType == SO2) {
        if(SO2x_.size() == 0) {
            SO2x_.push_back(1);
        } else {
            double previous = SO2x_.last();
            SO2x_.push_back(previous + 1);
        }
        SO2y_.push_back(value);
    } else {
        if(NOx_.size() == 0) {
            NOx_.push_back(1);
        } else {
            double previous = NOx_.last();
            NOx_.push_back(previous + 1);
        }
        NOy_.push_back(value);
    }
}

QVector<QVector<double>> Station::getAllData()
{
    QVector<QVector<double>> allData;
    allData.push_back(CO2x_);
    allData.push_back(CO2y_);
    allData.push_back(SO2x_);
    allData.push_back(SO2y_);
    allData.push_back(NOx_);
    allData.push_back(NOy_);

    return allData;
}


Station::~Station()
{

}
