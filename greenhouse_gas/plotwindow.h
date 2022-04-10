#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include "qcustomplot.h"
#include "datahandler.hh"
#include "station.hh"
#include "history.hh"

#include <QWidget>
#include <QMainWindow>

namespace Ui {
class PlotWindow;
}

class PlotWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PlotWindow(QWidget *parent = nullptr, dataHandler* datahandler = nullptr);
    ~PlotWindow();

private slots:
    void handleButton();

private:
    Ui::PlotWindow *ui;
    dataHandler* datahandler_;
    QVector<QColor> coloursSmear = {Qt::red, Qt::black, Qt::cyan};
    QVector<QColor> coloursStatfi = {Qt::blue, Qt::green, Qt::gray, Qt::magenta};
    int index_ = 0;
    QString smearStartDate_ = "";
    QString smearEndDate_ = "";

    void plotNewData(QVector<Station*> stations, QCustomPlot* customPlot);
    void plotHistoricalData(QVector<History*> historical, QCustomPlot* customPlot);

    const QString API_IN_TONNES = "Khk_yht";
    const QString API_INTENSITY = "Khk_yht_las";
    const QString API_INDEXED = "Khk_yht_index";
    const QString API_INTENSITY_INDEXED = "Khk_yht_las_index";

    const QString CO2_TONNES = "CO2 in tonnes";
    const QString CO2_INDEXED = "CO2 indexed";
    const QString CO2_INTENSITY = "CO2 intensity";
    const QString CO2_INTENSITY_INDEXED = "CO2 intesity indexed";

};

#endif // PLOTWINDOW_H
