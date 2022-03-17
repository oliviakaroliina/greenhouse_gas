#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Front page");

    connect(ui->smearCheckBox, &QRadioButton::clicked, this,
            &MainWindow::disableButtons);
    connect(ui->statfiCheckBox, &QRadioButton::clicked, this,
            &MainWindow::disableButtons);
    connect(ui->visualizePushButton, &QPushButton::clicked, this,
            &MainWindow::visualize);
    connect(ui->restartPushButton, &QPushButton::clicked, this,
            &MainWindow::restart);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QVector<QString> MainWindow::getApis()
{
    QVector<QString> apis = {};

    if (ui->smearCheckBox->isChecked())
    {
        apis.push_back("smear");
    }
    if (ui->statfiCheckBox->isChecked())
    {
        apis.push_back("statfi");
    }
    return apis;
}

QVector<QString> MainWindow::getMonitoringStations()
{
    QVector<QString> stations = {};

    if (ui->hyytialaCheckBox->isChecked())
    {
        stations.push_back("hyytiala");
    }
    if (ui->kumpulaCheckBox->isChecked())
    {
        stations.push_back("kumpula");
    }
    if (ui->varrioCheckBox->isChecked())
    {
        stations.push_back("varrio");
    }
    return stations;
}

QVector<QString> MainWindow::getGreenhouseGases()
{
    QVector<QString> gases = {};

    if (ui->CO2CheckBox->isChecked())
    {
        gases.push_back("co2");
    }
    if (ui->SO2CheckBox->isChecked())
    {
        gases.push_back("so2");
    }
    if (ui->NOxCheckBox->isChecked())
    {
        gases.push_back("nox");
    }
    return gases;
}

QString MainWindow::getDatatype()
{
    if (ui->rawRadioButton->isChecked())
    {
        return "raw";
    }
    else if (ui->averageRadioButton->isChecked())
    {
        return "average";
    }
    else if (ui->minimumRadioButton->isChecked())
    {
        return "minimum";
    }
    else if (ui->maximumRadioButton->isChecked())
    {
        return "maximum";
    }
    else
    {
        return "";
    }
}

QVector<QString> MainWindow::getDatasets()
{
    QVector<QString> datasets = {};

    if (ui->inTonnesCheckBox->isChecked())
    {
        datasets.push_back("in tonnes");
    }
    if (ui->intensityCheckBox->isChecked())
    {
        datasets.push_back("intensity");
    }
    if (ui->indexedCheckBox->isChecked())
    {
        datasets.push_back("indexed");
    }
    if (ui->intensityIndexedCheckBox->isChecked())
    {
        datasets.push_back("intensity indexed");
    }
    return datasets;
}

QDate MainWindow::getSmearStartDate()
{
    return ui->smearStartCalendar->selectedDate();
}

QDate MainWindow::getSmearEndDate()
{
    return ui->smearEndCalendar->selectedDate();
}

QDate MainWindow::getStatfiStartDate()
{
    return ui->statfiStartCalendar->selectedDate();
}

QDate MainWindow::getStatfiEndDate()
{
    return ui->statfiEndCalendar->selectedDate();
}

void MainWindow::disableButtons()
{
    // smear is checked and statfi is not
    if (ui->smearCheckBox->checkState()!=0 and
        ui->statfiCheckBox->checkState()==0)
    {
        ui->datasetLabel->setEnabled(false);
        ui->inTonnesCheckBox->setEnabled(false);
        ui->indexedCheckBox->setEnabled(false);
        ui->intensityCheckBox->setEnabled(false);
        ui->intensityIndexedCheckBox->setEnabled(false);
        ui->statfiStartLabel->setEnabled(false);
        ui->statfiEndLabel->setEnabled(false);
        ui->statfiStartCalendar->setEnabled(false);
        ui->statfiEndCalendar->setEnabled(false);
    }
    // statfi is checked and smear is not
    else if (ui->statfiCheckBox->checkState()!=0 and
        ui->smearCheckBox->checkState()==0)
    {
        ui->stationLabel->setEnabled(false);
        ui->hyytialaCheckBox->setEnabled(false);
        ui->kumpulaCheckBox->setEnabled(false);
        ui->varrioCheckBox->setEnabled(false);
        ui->gasLabel->setEnabled(false);
        ui->CO2CheckBox->setEnabled(false);
        ui->SO2CheckBox->setEnabled(false);
        ui->NOxCheckBox->setEnabled(false);
        ui->viewLabel->setEnabled(false);
        ui->rawRadioButton->setEnabled(false);
        ui->averageRadioButton->setEnabled(false);
        ui->minimumRadioButton->setEnabled(false);
        ui->maximumRadioButton->setEnabled(false);
        ui->smearStartLabel->setEnabled(false);
        ui->smearEndLabel->setEnabled(false);
        ui->smearStartCalendar->setEnabled(false);
        ui->smearEndCalendar->setEnabled(false);
    }
    // neither or both are checked
    else
    {
        ui->stationLabel->setEnabled(true);
        ui->hyytialaCheckBox->setEnabled(true);
        ui->kumpulaCheckBox->setEnabled(true);
        ui->varrioCheckBox->setEnabled(true);
        ui->gasLabel->setEnabled(true);
        ui->CO2CheckBox->setEnabled(true);
        ui->SO2CheckBox->setEnabled(true);
        ui->NOxCheckBox->setEnabled(true);
        ui->viewLabel->setEnabled(true);
        ui->rawRadioButton->setEnabled(true);
        ui->averageRadioButton->setEnabled(true);
        ui->minimumRadioButton->setEnabled(true);
        ui->maximumRadioButton->setEnabled(true);
        ui->smearStartLabel->setEnabled(true);
        ui->smearEndLabel->setEnabled(true);
        ui->smearStartCalendar->setEnabled(true);
        ui->smearEndCalendar->setEnabled(true);

        ui->datasetLabel->setEnabled(true);
        ui->inTonnesCheckBox->setEnabled(true);
        ui->indexedCheckBox->setEnabled(true);
        ui->intensityCheckBox->setEnabled(true);
        ui->intensityIndexedCheckBox->setEnabled(true);
        ui->statfiStartLabel->setEnabled(true);
        ui->statfiEndLabel->setEnabled(true);
        ui->statfiStartCalendar->setEnabled(true);
        ui->statfiEndCalendar->setEnabled(true);
    }
}

void MainWindow::visualize()
{
    p.show();
}

void MainWindow::restart()
{
    // Quits the previous program
    qApp->quit();
    // Starts a new one
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

