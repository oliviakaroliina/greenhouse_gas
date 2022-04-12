#ifndef HISTORY_HH
#define HISTORY_HH

#include <QObject>

class History
{
public:
    History(QString type = "", QVector<double> years = {}, QVector<double> values = {});

    // Returns the type of data
    QString getType();
    // Returns the vectors containing time and data
    QVector<double> getYears();
    QVector<double> getValues();

private:
    QString type_ = "";
    QVector<double> years_ = {};
    QVector<double> values_ = {};

};

#endif // HISTORY_HH
