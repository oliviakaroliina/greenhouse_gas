#include "history.hh"

History::History(QString type, QVector<double> years, QVector<double> values)
{
    type_ = type;
    years_ = years;
    values_ = values;
}

QString History::getType()
{
    return type_;
}

QVector<double> History::getYears()
{
    return years_;
}

QVector<double> History::getValues()
{
    return values_;
}
