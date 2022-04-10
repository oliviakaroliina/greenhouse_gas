#ifndef HISTORY_HH
#define HISTORY_HH

#include <QObject>

class History
{
public:
    History(QString type = "", QVector<double> years = {}, QVector<double> values = {});

    QString getType();

    QVector<double> getYears();
    QVector<double> getValues();

private:
    QString type_ = "";
    QVector<double> years_ = {};
    QVector<double> values_ = {};

    // tarviiko?
    const QString API_IN_TONNES = "Khk_yht";
    const QString API_INTENSITY = "Khk_yht_las";
    const QString API_INDEXED = "Khk_yht_index";
    const QString API_INTENSITY_INDEXED = "Khk_yht_las_index";
};

#endif // HISTORY_HH
