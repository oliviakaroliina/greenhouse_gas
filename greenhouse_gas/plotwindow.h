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

};

#endif // PLOTWINDOW_H
