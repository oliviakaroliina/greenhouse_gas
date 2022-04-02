#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>
#include <fstream>
#include <QProcess>

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
    connect(ui->quitPushButton, &QPushButton::clicked, this,
            &MainWindow::quitButtonClicked);

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
    if (ui->rawRadioButton->isChecked())
    {
        return RAW;
    }
    else if (ui->averageRadioButton->isChecked())
    {
        return AVERAGE;
    }
    else if (ui->minimumRadioButton->isChecked())
    {
        return MINIMUM;
    }
    else if (ui->maximumRadioButton->isChecked())
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
    // Clear all -checkbox is checked
    else if (ui->clearAllCheckBox->checkState()!=0)
    {
        clearAll();
    }
    emit visualizeButtonPressed();
}

void MainWindow::restart()
{
    // Save selections -checkbox is checked
    if (ui->saveSelectionsCheckBox->checkState()!=0)
    {
        saveSelections();
    }
    // Clear all -checkbox is checked
    else if (ui->clearAllCheckBox->checkState()!=0)
    {
        clearAll();
    }
    // Quits the previous program
    qApp->quit();
    // Starts a new one
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

void MainWindow::quitButtonClicked()
{
    // Save selections -checkbox is checked
    if (ui->saveSelectionsCheckBox->checkState()!=0)
    {
        saveSelections();
    }
    // Clear all -checkbox is checked
    else if (ui->clearAllCheckBox->checkState()!=0)
    {
        clearAll();
    }
}

void MainWindow::disableStatfiButtons()
{
    // Disables buttons
    ui->datasetLabel->setEnabled(false);
    ui->inTonnesCheckBox->setEnabled(false);
    ui->indexedCheckBox->setEnabled(false);
    ui->intensityCheckBox->setEnabled(false);
    ui->intensityIndexedCheckBox->setEnabled(false);
    ui->statfiStartLabel->setEnabled(false);
    ui->statfiEndLabel->setEnabled(false);
    ui->statfiStartCalendar->setEnabled(false);
    ui->statfiEndCalendar->setEnabled(false);

    // Removes possible selections
    ui->inTonnesCheckBox->setCheckState(Qt::Unchecked);
    ui->indexedCheckBox->setCheckState(Qt::Unchecked);
    ui->intensityCheckBox->setCheckState(Qt::Unchecked);
    ui->intensityIndexedCheckBox->setCheckState(Qt::Unchecked);
}

void MainWindow::disableSmearButtons()
{
    // Disables buttons
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

    // Removes possible selections
    ui->hyytialaCheckBox->setCheckState(Qt::Unchecked);
    ui->kumpulaCheckBox->setCheckState(Qt::Unchecked);
    ui->varrioCheckBox->setCheckState(Qt::Unchecked);
    ui->CO2CheckBox->setCheckState(Qt::Unchecked);
    ui->SO2CheckBox->setCheckState(Qt::Unchecked);
    ui->NOxCheckBox->setCheckState(Qt::Unchecked);

    ui->rawRadioButton->setAutoExclusive(false);
    ui->rawRadioButton->setChecked(false);
    ui->rawRadioButton->setAutoExclusive(true);

    ui->averageRadioButton->setAutoExclusive(false);
    ui->averageRadioButton->setChecked(false);
    ui->averageRadioButton->setAutoExclusive(true);

    ui->minimumRadioButton->setAutoExclusive(false);
    ui->minimumRadioButton->setChecked(false);
    ui->minimumRadioButton->setAutoExclusive(true);

    ui->maximumRadioButton->setAutoExclusive(false);
    ui->maximumRadioButton->setChecked(false);
    ui->maximumRadioButton->setAutoExclusive(true);
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
    std::ofstream fileObject(SELECTIONS_FILE);

    // Writes the information to the file
    // - The metadata is first in the row, and after that :
    // - Different informations are in their own lines
    // - Vectors contents are separated with :
    // - Dates are represented as day:month:year

    fileObject << "apis:";
    for (QString& api : apis)
    {
        fileObject << api.toStdString() << ":";
    }
    fileObject << std::endl << "stations:";
    for (QString& station : stations)
    {
        fileObject << station.toStdString() << ":";
    }
    fileObject << std::endl << "gases:";
    for (QString& gas : gases)
    {
        fileObject << gas.toStdString() << ":";
    }
    fileObject << std::endl << "datatype:" << datatype.toStdString() <<
                   std::endl << "datasets:";
    for (QString& dataset : datasets)
    {
        fileObject << dataset.toStdString() << ":";
    }
    fileObject << std::endl << "smearstart:";
    fileObject << smearstart.day() << ":" << smearstart.month() << ":" <<
                   smearstart.year() << ":" << std::endl << "smearend:";
    fileObject << smearend.day() << ":" << smearend.month() << ":" <<
                   smearend.year() << ":" << std::endl << "statfistart:";
    fileObject << statfistart.day() << ":" << statfistart.month() << ":" <<
                   statfistart.year() << ":" << std::endl << "statfiend:";
    fileObject << statfiend.day() << ":" << statfiend.month() << ":" <<
                   statfiend.year() << ":" << std::endl;

    // Closes the file
    fileObject.close();
}

void MainWindow::clearAll()
{
    // Opens the file for writing nothing
    std::ofstream fileObject;
    fileObject.open(SELECTIONS_FILE, std::ofstream::out | std::ofstream::trunc);
    // Closes the file
    fileObject.close();
}

void MainWindow::readSelections()
{
    // Opens the file for reading
    std::ifstream fileObject(SELECTIONS_FILE);
    if (fileObject)
    {
        std::string row;
        int rowNumber = 1;
        while (getline(fileObject, row))
        {
            std::vector<std::string> parts = split(row, ':', true);

            // Based on the row's information, the right information
            // will be added to UI
            if (parts.at(0) == "apis")
            {
                setSelections(1, 0, 0, 0, parts);
            }
            else if (parts.at(0) == "stations")
            {
                setSelections(0, 1, 0, 0, parts);
            }
            else if (parts.at(0) == "gases")
            {
                setSelections(0, 0, 1, 0, parts);
            }
            else if (parts.at(0) == "datatype" and parts.size()==2)
            {
                setDatatype(parts.at(1));
            }
            else if (parts.at(0) == "datasets")
            {
                setSelections(0, 0, 0, 1, parts);
            }
            else if (parts.at(0) == "smearstart")
            {
                // Indexing starts from 1, because the first word in
                // the row is metadata (explains the data type), so
                // the actual information starts from the second word
                setDate(1, 0, 0, 0, std::stoi(parts.at(1)),
                        std::stoi(parts.at(2)), std::stoi(parts.at(3)));
            }
            else if (parts.at(0) == "smearend")
            {
                setDate(0, 1, 0, 0, std::stoi(parts.at(1)),
                        std::stoi(parts.at(2)), std::stoi(parts.at(3)));
            }
            else if (parts.at(0) == "statfistart")
            {
                setDate(0, 0, 1, 0, std::stoi(parts.at(1)),
                        std::stoi(parts.at(2)), std::stoi(parts.at(3)));
            }
            else if (parts.at(0) == "statfiend")
            {
                setDate(0, 0, 0, 1, std::stoi(parts.at(1)),
                        std::stoi(parts.at(2)), std::stoi(parts.at(3)));
            }
            ++rowNumber;
        }
        // Closes the file
        fileObject.close();
    }
    disableButtons();
}

std::vector<std::string> MainWindow::split(const std::string& s, const char&
                                           separator, bool ignoreEmpty)
{
    std::vector<std::string> result;
    // For saving the rest of the string after splitting
    std::string tmp = s;

    while (tmp.find(separator) != std::string::npos)
    {
        // Saves the part to a variable
        std::string newPart = tmp.substr(0, tmp.find(separator));

        // Saves rest of the string without the part to the variable
        tmp = tmp.substr(tmp.find(separator)+1, tmp.size());

        // If the part is empty and the empty parts are wanted too
        // or vice versa, adds the part to the result
        if (not(ignoreEmpty and newPart.empty()))
        {
            result.push_back(newPart);
        }
    }
    // Adds the last part to the result
    if (not(ignoreEmpty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

void MainWindow::setSelections(bool apis, bool stations, bool gases,
                               bool datasets, std::vector<std::string> &info)
{
    if (apis)
    {
        for (std::string& api : info)
        {
            if (api == SMEAR.toStdString())
            {
                // Sets check box as ticked
                ui->smearCheckBox->setCheckState(Qt::Checked);
            }
            if (api == STATFI.toStdString())
            {
                ui->statfiCheckBox->setCheckState(Qt::Checked);
            }
        }
    }
    else if (stations)
    {
        for (std::string& station : info)
        {
            if (station == HYYTIALA.toStdString())
            {
                ui->hyytialaCheckBox->setCheckState(Qt::Checked);
            }
            if (station == KUMPULA.toStdString())
            {
                ui->kumpulaCheckBox->setCheckState(Qt::Checked);
            }
            if (station == VARRIO.toStdString())
            {
                ui->varrioCheckBox->setCheckState(Qt::Checked);
            }
        }
    }
    else if (gases)
    {
        for (std::string& gas : info)
        {
            if (gas == CO2.toStdString())
            {
                ui->CO2CheckBox->setCheckState(Qt::Checked);
            }
            if (gas == SO2.toStdString())
            {
                ui->SO2CheckBox->setCheckState(Qt::Checked);
            }
            if (gas == NOX.toStdString())
            {
                ui->NOxCheckBox->setCheckState(Qt::Checked);
            }
        }
    }
    else if (datasets)
    {
        for (std::string& dataset : info)
        {
            if (dataset == IN_TONNES.toStdString())
            {
                ui->inTonnesCheckBox->setCheckState(Qt::Checked);
            }
            if (dataset == INTENSITY.toStdString())
            {
                ui->intensityCheckBox->setCheckState(Qt::Checked);
            }
            if (dataset == INDEXED.toStdString())
            {
                ui->indexedCheckBox->setCheckState(Qt::Checked);
            }
            if (dataset == INTENSITY_INDEXED.toStdString())
            {
                ui->intensityIndexedCheckBox->setCheckState(Qt::Checked);
            }
        }
    }
}

void MainWindow::setDatatype(std::string &datatype)
{
    if (datatype == RAW.toStdString())
    {
        ui->rawRadioButton->setChecked(true);
    }
    else if (datatype == AVERAGE.toStdString())
    {
        ui->averageRadioButton->setChecked(true);
    }
    else if (datatype == MINIMUM.toStdString())
    {
        ui->minimumRadioButton->setChecked(true);
    }
    else if (datatype == MAXIMUM.toStdString())
    {
        ui->maximumRadioButton->setChecked(true);
    }
}

void MainWindow::setDate(bool smearstart, bool smearend, bool statfistart,
                         bool statfiend, int day, int month, int year)
{
    if (smearstart)
    {
        ui->smearStartCalendar->setSelectedDate({year, month, day});
    }
    else if (smearend)
    {
        ui->smearEndCalendar->setSelectedDate({year, month, day});
    }
    else if (statfistart)
    {
        ui->statfiStartCalendar->setSelectedDate({year, month, day});
    }
    else if (statfiend)
    {
        ui->statfiEndCalendar->setSelectedDate({year, month, day});
    }
}
