#include "plotwindow.h"
#include "ui_plotwindow.h"

PlotWindow::PlotWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlotWindow)
{
    ui->setupUi(this);
    connect(ui->returnPushButton, &QPushButton::released, this, &PlotWindow::handleButton);

    // Fake container for data for mid term
    QVector<double> x1(20), y1(20);
    QVector<double> x2(100), y2(100);
    QVector<double> x3(20), y3(20);
    for(int i = 0; i < x1.size(); i++) {
        x1[i] = i;
        y1[i] = 1000*i - (23/45) * i;
    }
    for(int j = 0; j < x2.size(); j++) {
        x2[j] = j;
        y2[j] = 1504*j - 0.832*j;
    }
    for(int k = 0; k < x1.size(); k++) {
        x3[k] = k/(double)(x1.size()-1)*10;
        y3[k] = qCos(x1[k]*0.85+qSin(x1[k]*0.165+1.1))*qSin(x1[k]*0.50)+1.7;
    }

    auto customPlot = ui->customPlot;
    customPlot->setAutoAddPlottableToLegend(false);
    customPlot->plotLayout()->clear();
    // Create 2 graphs
    QCPAxisRect *first = new QCPAxisRect(customPlot);
    first->setupFullAxesBox(true);
    QCPAxisRect *second = new QCPAxisRect(customPlot);
    second->setupFullAxesBox(true);
    // Add them to the window
    customPlot->plotLayout()->addElement(0, 0, first);
    customPlot->plotLayout()->addElement(1, 0, second);
    // Info boards
    QCPLegend *legend1 = new QCPLegend;
    first->insetLayout()->addElement(legend1,
                                     Qt::AlignTop|Qt::AlignRight);
    legend1->setLayer("legend");
    QCPLegend *legend2 = new QCPLegend;
    second->insetLayout()->addElement(legend2,
                                     Qt::AlignTop|Qt::AlignRight);
    legend2->setLayer("legend");
    // Make the graphs even sized
    QCPMarginGroup *marginGroup = new QCPMarginGroup(customPlot);
    second->setMarginGroup(QCP::msLeft | QCP::msRight, marginGroup);
    // Move axes on axes layer and grids on grid layer
    foreach (QCPAxisRect *rect, customPlot->axisRects())
    {
      foreach (QCPAxis *axis, rect->axes())
      {
        axis->setLayer("axes");
        axis->grid()->setLayer("grid");
      }
    }
    // Plots for graph 1
    QCPGraph *graph1 = customPlot->addGraph(first->axis(QCPAxis::atBottom),
                                            first->axis(QCPAxis::atLeft));
    graph1->setData(x1, y1);
    graph1->setPen(QPen(Qt::cyan));
    graph1->setName("CO2");

    QCPGraph *graph2 = customPlot->addGraph(first->axis(QCPAxis::atBottom),
                                            first->axis(QCPAxis::atLeft));
    graph2->setData(x2, y2);
    graph2->setPen(QPen(Qt::magenta));
    graph2->setName("NO2");

    legend1->addItem(new QCPPlottableLegendItem(legend1, graph1));
    legend1->addItem(new QCPPlottableLegendItem(legend1, graph2));

    graph1->rescaleAxes(true);
    // One plot for graph 2
    QCPGraph *graph3 = customPlot->addGraph(second->axis(QCPAxis::atBottom),
                                            second->axis(QCPAxis::atLeft));
    graph3->setData(x3, y3);
    graph3->setPen(QPen(Qt::red));
    graph3->setName("CO2 intensity");

    legend2->addItem(new QCPPlottableLegendItem(legend2, graph3));

}

PlotWindow::~PlotWindow()
{
    delete ui;
}

void PlotWindow::handleButton()
{
    close();
}
