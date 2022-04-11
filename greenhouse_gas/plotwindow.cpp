#include "plotwindow.h"
#include "ui_plotwindow.h"

PlotWindow::PlotWindow(QWidget *parent, dataHandler* datahandler) :
    QWidget(parent),
    ui(new Ui::PlotWindow)
{
    ui->setupUi(this);
    setWindowTitle("Plots");

    datahandler_ = datahandler;
    connect(ui->returnPushButton, &QPushButton::released, this, &PlotWindow::handleButton);

    auto customPlot = ui->customPlot;
    customPlot->setAutoAddPlottableToLegend(false);
    customPlot->plotLayout()->clear();

    // Get new and historical data
    QVector<Station*> stations = datahandler_->getStations();
    QVector<History*> historical = datahandler_->getHistorical();

    // Plot if there is data
    if(!stations.empty() and !historical.empty()) {
        smearStartDate_ = datahandler->getStartDate();
        smearEndDate_ = datahandler->getEndDate();
        plotNewData(stations, customPlot);
        plotHistoricalData(historical, customPlot);
    } else if(!stations.empty() and historical.empty()) {
        smearStartDate_ = datahandler->getStartDate();
        smearEndDate_ = datahandler->getEndDate();
        plotNewData(stations, customPlot);
    } else {
        plotHistoricalData(historical, customPlot);
    }

}

PlotWindow::~PlotWindow()
{
    delete ui;
}

void PlotWindow::handleButton()
{
    close();
}

void PlotWindow::plotNewData(QVector<Station*> stations, QCustomPlot *customPlot)
{
    for(int i = 0; i < stations.size(); i++) {
        Station* station = stations.at(i);

        QVector<QVector<double>> allData = station->getAllData(); //CO2x, CO2y, SO2x, SO2y, NOx, NOy

        QCPAxisRect *axisRect = new QCPAxisRect(customPlot, false);
        axisRect->setupFullAxesBox(true);
        customPlot->plotLayout()->addElement(yIndex_, xIndex_, axisRect);
        yIndex_++;

        QCPLegend *legend = new QCPLegend;
        axisRect->insetLayout()->addElement(legend,
                                         Qt::AlignTop|Qt::AlignRight);
        legend->setLayer(LEGEND);

        // insert data to graphs
        int smallest = 0;
        int largest = 0;
        for(int i = 0; i < allData.size(); i+= 2) {
            QVector<double> dataX = allData.at(i);
            QVector<double> dataY = allData.at(i+1);

            if(!dataX.empty() and !dataY.empty()) {
                int max = *std::max_element(dataY.begin(), dataY.end());
                int min = *std::min_element(dataY.begin(), dataY.end());
                if(max > largest) {
                    largest = max;
                }
                if(min < smallest) {
                    smallest = min;
                }

                QCPGraph *graph = customPlot->addGraph(axisRect->axis(QCPAxis::atBottom),
                                                        axisRect->axis(QCPAxis::atLeft));
                graph->setData(dataX, dataY);
                if(i == 0) {
                    graph->setName(CO2);
                    graph->setPen(QPen(coloursSmear.at(RED)));
                } else if(i == 2) {
                    graph->setName(SO2);
                    graph->setPen(QPen(coloursSmear.at(BLACK)));
                } else if(i == 4) {
                    graph->setName(NO);
                    graph->setPen(QPen(coloursSmear.at(CYAN)));
                }
                legend->addItem(new QCPPlottableLegendItem(legend, graph));
                graph->valueAxis()->setScaleType(QCPAxis::stLogarithmic);
                graph->valueAxis()->setRange(smallest, largest + (largest / 10));
                graph->rescaleKeyAxis();
                graph->valueAxis()->setLabel(station->getName());
                QString xLabel = "From " + smearStartDate_ + " to " + smearEndDate_ + " data taken every hour.\n"
                                         + "Null and zero values ignored.";
                graph->keyAxis()->setLabel(xLabel);
            }
        }
    }
}

void PlotWindow::plotHistoricalData(QVector<History*> historical, QCustomPlot *customPlot)
{
    QCPAxisRect *axisRectHistory = new QCPAxisRect(customPlot, false);
    axisRectHistory->setupFullAxesBox(true);
    customPlot->plotLayout()->addElement(yIndex_, xIndex_, axisRectHistory);

    QCPLegend *legendHistory = new QCPLegend;
    axisRectHistory->insetLayout()->addElement(legendHistory,
                                     Qt::AlignTop|Qt::AlignRight);
    legendHistory->setLayer(LEGEND);

    int smallest = 0;
    int largest = 0;
    for(int j = 0; j < historical.size(); j++) {
        History* history = historical.at(j);
        QVector<double> years = history->getYears();
        QVector<double> values = history->getValues();
        int max = *std::max_element(values.begin(), values.end());
        int min = *std::min_element(values.begin(), values.end());
        if(max > largest) {
            largest = max;
        }
        if(min < smallest) {
            smallest = min;
        }

        QCPGraph *graph = customPlot->addGraph(axisRectHistory->axis(QCPAxis::atBottom),
                                                axisRectHistory->axis(QCPAxis::atLeft));
        graph->setData(years, values);
        QString type = history->getType();
        if(type == API_IN_TONNES and historical.size() != 1) {
            graph->setName(CO2_TONNES);
        } else if(type == API_INTENSITY) {
            graph->setName(CO2_INTENSITY);
        } else if(type == API_INDEXED) {
            graph->setName(CO2_INDEXED);
        } else {
            graph->setName(CO2_INTENSITY_INDEXED);
        }

        graph->setPen(QPen(coloursStatfi.at(j)));

        // Logarithmic scale if more than one graph
        if(historical.size() > 1 and type == API_IN_TONNES) {
            graph->valueAxis()->setScaleType(QCPAxis::stLogarithmic);
            graph->valueAxis()->setRange(smallest, largest + (largest / 10));
            graph->rescaleKeyAxis();
        } else {
            graph->valueAxis()->setRange(smallest, largest + (largest / 10));
            graph->rescaleKeyAxis();
        }
        graph->keyAxis()->setLabel(YEAR);

        legendHistory->addItem(new QCPPlottableLegendItem(legendHistory, graph));
    }
}
