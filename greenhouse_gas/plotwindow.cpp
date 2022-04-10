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
            QVector<double> dataX = allData.at(i); // how many eli aika?
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
            }


            if(dataX.size() != 0 && dataY.size() != 0) {
                QCPGraph *graph = customPlot->addGraph(axisRect->axis(QCPAxis::atBottom),
                                                        axisRect->axis(QCPAxis::atLeft));
                graph->setData(dataX, dataY);
                if(i == 0) {
                    graph->setName("CO2");
                    graph->setPen(QPen(coloursSmear.at(0)));
                } else if(i == 2) {
                    graph->setName("SO2");
                    graph->setPen(QPen(coloursSmear.at(1)));
                } else if(i == 4) {
                    graph->setName("NOx");
                    graph->setPen(QPen(coloursSmear.at(2)));
                }
                legend->addItem(new QCPPlottableLegendItem(legend, graph));
                graph->valueAxis()->setScaleType(QCPAxis::stLogarithmic); //logaritminen!!
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

}
