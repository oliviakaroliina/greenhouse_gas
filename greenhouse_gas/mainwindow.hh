#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "plotwindow.h"

#include <QMainWindow>
#include <QCheckBox>
#include <QRadioButton>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Returns selected api names in lower case
    // e.g. {"smear", "statfi"}
    // If no apis are selected, returns empty vector
    QVector<QString> getApis();

    // Returns monitoring stations in lower case and without ä and ö
    // e.g. {"hyytiala", "varrio"}
    // If no monitoring station is selected, returns empty vector
    QVector<QString> getMonitoringStations();

    // Returns greenhouse gases in lower case
    // e.g. {"co2", "nox"}
    // If no greenhouse gas is selected, returns empty vector
    QVector<QString> getGreenhouseGases();

    // Returns datatype in lower case
    // e.g. "minimum"
    // If no datatype is selected, returns empty string
    QString getDatatype();

    // Returns datasets in lower case
    // e.g. {"in tonnes", "indexed", "intensity indexed"}
    // If no dataset is selected, returns empty vector
    QVector<QString> getDatasets();

    // Returns Smear start date
    QDate getSmearStartDate();

    // Returns Smear end date
    QDate getSmearEndDate();

    // Returns Statfi start date
    QDate getStatfiStartDate();

    // Returns Statfi end date
    QDate getStatfiEndDate();

private slots:

    // Enables all the SMEAR selections in UI
    void disableButtons();

    // Starts the next window
    void save();

    // Restarts the program
    void restart();

private:
    Ui::MainWindow *ui;
    PlotWindow p;

};
#endif // MAINWINDOW_HH
