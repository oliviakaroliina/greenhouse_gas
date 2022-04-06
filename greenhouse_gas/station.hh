#ifndef STATION_H
#define STATION_H

#include <QObject>
#include <QDateTime>

class Station
{
public:
    Station(QString name = "", QString gasType = "");

    QString getName();
    QString getGasType();
    void insertValues(QString time, double value, QString gasType);
    QVector<QVector<double>> getAllData();
    void testi();

    ~Station();

private:
    QString name_ = "";
    QString gasType_ = "";

    // nää alapuolelta vektoreihin
    QString time_ = "";

    // Three vectors per station for CO2, SO2, NOx
    // x being time
    QVector<double> CO2x_ = {};
    QVector<double> CO2y_ = {};
    QVector<double> SO2x_ = {};
    QVector<double> SO2y_ = {};
    QVector<double> NOx_ = {};
    QVector<double> NOy_ = {};

    const QString CO2 = "CO2";
    const QString SO2 = "SO2";
    const QString NOX = "NOx";
};

#endif // STATION_H
