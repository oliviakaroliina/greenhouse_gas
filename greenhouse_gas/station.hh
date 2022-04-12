#ifndef STATION_H
#define STATION_H

#include <QObject>
#include <QDateTime>

class Station
{
public:
    Station(QString name = "");

    // Returns the name of the station
    QString getName();
    // Inserts values
    void insertValues(double value, QString gasType);
    // Returns all the vectors
    QVector<QVector<double>> getAllData();

    ~Station();

private:
    // Name of the station
    QString name_ = "";

    // Vectors for storing the data, each gas type has its own
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
