#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>
#include <fstream>

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

    readSelections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QVector<QString> MainWindow::getApis()
{
    QVector<QString> apis = {};

    if (ui->smearCheckBox->checkState()!=0)
    {
        apis.push_back(SMEAR);
    }
    if (ui->statfiCheckBox->checkState()!=0)
    {
        apis.push_back(STATFI);
    }
    return apis;
}

QVector<QString> MainWindow::getMonitoringStations()
{
    QVector<QString> stations = {};

    if (ui->hyytialaCheckBox->checkState()!=0)
    {
        stations.push_back(HYYTIALA);
    }
    if (ui->kumpulaCheckBox->checkState()!=0)
    {
        stations.push_back(KUMPULA);
    }
    if (ui->varrioCheckBox->checkState()!=0)
    {
        stations.push_back(VARRIO);
    }
    return stations;
}

QVector<QString> MainWindow::getGreenhouseGases()
{
    QVector<QString> gases = {};

    if (ui->CO2CheckBox->checkState()!=0)
    {
        gases.push_back(CO2);
    }
    if (ui->SO2CheckBox->checkState()!=0)
    {
        gases.push_back(SO2);
    }
    if (ui->NOxCheckBox->checkState()!=0)
    {
        gases.push_back(NOX);
    }
    return gases;
}

QString MainWindow::getDatatype()
{
    if (ui->rawRadioButton->isDown())
    {
        return RAW;
    }
    else if (ui->averageRadioButton->isDown())
    {
        return AVERAGE;
    }
    else if (ui->minimumRadioButton->isDown())
    {
        return MINIMUM;
    }
    else if (ui->maximumRadioButton->isDown())
    {
        return MAXIMUM;
    }
    else
    {
        return NO_VALUE;
    }
}

QVector<QString> MainWindow::getDatasets()
{
    QVector<QString> datasets = {};

    if (ui->inTonnesCheckBox->checkState()!=0)
    {
        datasets.push_back(IN_TONNES);
    }
    if (ui->intensityCheckBox->checkState()!=0)
    {
        datasets.push_back(INTENSITY);
    }
    if (ui->indexedCheckBox->checkState()!=0)
    {
        datasets.push_back(INDEXED);
    }
    if (ui->intensityIndexedCheckBox->checkState()!=0)
    {
        datasets.push_back(INTENSITY_INDEXED);
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
    // Smear is checked and statfi is not
    if (ui->smearCheckBox->checkState()!=0 and
        ui->statfiCheckBox->checkState()==0)
    {
        disableStatfiButtons();
    }
    // Statfi is checked and smear is not
    else if (ui->statfiCheckBox->checkState()!=0 and
             ui->smearCheckBox->checkState()==0)
    {
        disableSmearButtons();
    }
    // Neither or both are checked
    else
    {
        enableAllButtons();
    }
}

void MainWindow::visualize()
{
    // Save selections -checkbox is checked
    if (ui->saveSelectionsCheckBox->checkState()!=0)
    {
        saveSelections();
    }
    p.show();
}

void MainWindow::restart()
{
    // Quits the previous program
    qApp->quit();
    // Starts a new one
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

void MainWindow::disableStatfiButtons()
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

void MainWindow::disableSmearButtons()
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

void MainWindow::enableAllButtons()
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

void MainWindow::saveSelections()
{
    // Fetches selections
    QVector<QString> apis = getApis();
    QVector<QString> stations = getMonitoringStations();
    QVector<QString> gases = getGreenhouseGases();
    QString datatype = getDatatype();
    QVector<QString> datasets = getDatasets();
    QDate smearstart = getSmearStartDate();
    QDate smearend = getSmearEndDate();
    QDate statfistart = getStatfiStartDate();
    QDate statfiend = getStatfiEndDate();

    // Opens the file for writing
    std::ofstream file_object(SELECTIONS_FILE);

    // Writes the information to the file
    // - Vectors contents are separated with :
    // - Dates are represented as day:month:year
    // - Different informations are in their own lines
    for (QString& api : apis)
    {
        file_object << api.toStdString() << ":";
    }
    file_object << std::endl;
    for (QString& station : stations)
    {
        file_object << station.toStdString() << ":";
    }
    file_object << std::endl;
    for (QString& gas : gases)
    {
        file_object << gas.toStdString() << ":";
    }
    file_object << std::endl << datatype.toStdString() << std::endl;
    for (QString& dataset : datasets)
    {
        file_object << dataset.toStdString() << ":";
    }
    file_object << std::endl;
    file_object << smearstart.day() << ":" << smearstart.month() << ":" <<
                   smearstart.year() << ":" << std::endl;
    file_object << smearend.day() << ":" << smearend.month() << ":" <<
                   smearend.year() << ":" << std::endl;
    file_object << statfistart.day() << ":" << statfistart.month() << ":" <<
                   statfistart.year() << ":" << std::endl;
    file_object << statfiend.day() << ":" << statfiend.month() << ":" <<
                   statfiend.year() << ":" << std::endl;

    // Closes the file
    file_object.close();
}

void MainWindow::readSelections()
{
    // Opens the file for reading
    std::ifstream file_object(SELECTIONS_FILE);
    if (file_object)
    {
        std::string row;
        while (getline(file_object, row))
        {
            if (row != "")
            {
                std::vector<std::string> parts = split(row, ':', true);
                // HANDLE THE DATA HERE
            }
        }
        // Closes the file
        file_object.close();
    }
}

std::vector<std::string> MainWindow::split(const std::string& s, const char&
                                           separator, bool ignore_empty)
{
    std::vector<std::string> result;
    // For saving the rest of the string after splitting
    std::string tmp = s;

    while (tmp.find(separator) != std::string::npos)
    {
        // Saves the part to a variable
        std::string new_part = tmp.substr(0, tmp.find(separator));

        // Saves rest of the string without the part to the variable
        tmp = tmp.substr(tmp.find(separator)+1, tmp.size());

        // If the part is empty and the empty parts are wanted too
        // or vice versa, adds the part to the result
        if (not(ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    // Adds the last part to the result
    if (not(ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

