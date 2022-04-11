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
    if(!stations.empty()) {
        smearStartDate_ = datahandler->getStartDate();
        smearEndDate_ = datahandler->getEndDate();
        plotNewData(stations, customPlot);
    }
    if(!historical.empty()) {
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
        customPlot->plotLayout()->addElement(index_, 0, axisRect);
        index_++;

        QCPLegend *legend = new QCPLegend;
        axisRect->insetLayout()->addElement(legend,
                                         Qt::AlignTop|Qt::AlignRight);
        legend->setLayer("legend");

        // Move axes on axes layer and grids on grid layer
        foreach (QCPAxisRect *rect, customPlot->axisRects())
        {
          foreach (QCPAxis *axis, rect->axes())
          {
            axis->setLayer("axes");
            axis->grid()->setLayer("grid");
          }
        }

        // insert data to graphs
        int smallest = 0;
        int largest = 0;
        for(int i = 0; i < allData.size(); i+= 2) {
            QVector<double> dataX = allData.at(i);
            QVector<double> dataY = allData.at(i+1); // value

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
                    graph->setName("CO2");
                    graph->setPen(QPen(coloursSmear.at(RED)));
                } else if(i == 2) {
                    graph->setName("SO2");
                    graph->setPen(QPen(coloursSmear.at(BLACK)));
                } else if(i == 4) {
                    graph->setName("NOx");
                    graph->setPen(QPen(coloursSmear.at(CYAN)));
                }
                legend->addItem(new QCPPlottableLegendItem(legend, graph));
                graph->valueAxis()->setScaleType(QCPAxis::stLogarithmic);
                graph->valueAxis()->setRange(smallest, largest + (largest / 10));
                graph->rescaleKeyAxis();
                graph->valueAxis()->setLabel(station->getName());
                QString xLabel = "From " + smearStartDate_ + " to " + smearEndDate_ + " data taken every hour.";
                graph->keyAxis()->setLabel(xLabel);
            }
        }
    }
}

void PlotWindow::plotHistoricalData(QVector<History*> historical, QCustomPlot *customPlot)
{
    QCPAxisRect *axisRectHistory = new QCPAxisRect(customPlot, false);
    axisRectHistory->setupFullAxesBox(true);
    customPlot->plotLayout()->addElement(index_, 0, axisRectHistory);

    QCPLegend *legendHistory = new QCPLegend;
    axisRectHistory->insetLayout()->addElement(legendHistory,
                                     Qt::AlignTop|Qt::AlignRight);
    legendHistory->setLayer("legend");

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

        // Move axes on axes layer and grids on grid layer
        foreach (QCPAxisRect *rect, customPlot->axisRects())
        {
          foreach (QCPAxis *axis, rect->axes())
          {
            axis->setLayer("axes");
            axis->grid()->setLayer("grid");
          }
        }
        QCPGraph *graph = customPlot->addGraph(axisRectHistory->axis(QCPAxis::atBottom),
                                                axisRectHistory->axis(QCPAxis::atLeft));
        graph->setData(years, values);
        QString type = history->getType();
        // if CO2 in tonnes and more selected, then use logarithmic scale
        if(type == API_IN_TONNES and historical.size() != 1) {
            graph->setName(CO2_TONNES);
            graph->valueAxis()->setScaleType(QCPAxis::stLogarithmic);
            graph->valueAxis()->setRange(smallest, largest + (largest / 10));
            graph->rescaleKeyAxis();
        } else if(type == API_IN_TONNES) {
            graph->setName(CO2_TONNES);
            graph->valueAxis()->setRange(0, largest + (largest / 10));
            graph->rescaleKeyAxis();
        } else if(type == API_INTENSITY) {
            graph->setName(CO2_INTENSITY);
            graph->valueAxis()->setRange(0, largest + (largest / 10));
            graph->rescaleKeyAxis();
        } else if(type == API_INDEXED) {
            graph->setName(CO2_INDEXED);
            graph->valueAxis()->setRange(0, largest + (largest / 10));
            graph->rescaleKeyAxis();
        } else {
            graph->setName(CO2_INTENSITY_INDEXED);
            graph->valueAxis()->setRange(0, largest + (largest / 10));
            graph->rescaleKeyAxis();
        }

        graph->setPen(QPen(coloursStatfi.at(j)));
        graph->keyAxis()->setLabel("Years");

        legendHistory->addItem(new QCPPlottableLegendItem(legendHistory, graph));
    }
}
