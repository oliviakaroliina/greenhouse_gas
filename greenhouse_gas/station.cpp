#include "station.hh"

Station::Station(QString name, QString gasType)
{
    qDebug() << "Station";
    name_ = name;
    gasType_ = gasType;
}

QString Station::getName()
{
    return name_;
}

QString Station::getGasType()
{
    return gasType_;
}

void Station::insertValues(QString time, double value, QString gasType)
{
    time.remove(10, 1);
    QDateTime date = QDateTime::fromString(time,"yyyy-MM-ddhh:mm:ss.zzz");
    //qDebug() << date;
    double timeAxis = date.currentSecsSinceEpoch();

    if(gasType == CO2) {
        CO2x_.push_back(timeAxis);
        CO2y_.push_back(value);
    } else if(gasType == SO2) {
        SO2x_.push_back(timeAxis);
        SO2y_.push_back(value);
    } else {
        NOx_.push_back(timeAxis);
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

void Station::testi()
{
    qDebug() << CO2x_.at(0);
    qDebug() << CO2y_.at(0);
}

Station::~Station()
{

}
