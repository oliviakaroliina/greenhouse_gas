#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

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

signals:
    void visualizeButtonPressed();

private slots:

    // Disables or enables buttons based on api choice
    void disableButtons();

    // Starts the next window
    void visualize();

    // Restarts the program
    void restart();

private:
    Ui::MainWindow *ui;

    const std::string SELECTIONS_FILE = "selections.txt";
    const QString NO_VALUE = "";
    const QString SMEAR = "smear";
    const QString STATFI = "statfi";
    const QString HYYTIALA = "hyytiala";
    const QString KUMPULA = "kumpula";
    const QString VARRIO = "varrio";
    const QString CO2 = "co2";
    const QString SO2 = "so2";
    const QString NOX = "nox";
    const QString RAW = "raw";
    const QString AVERAGE = "average";
    const QString MINIMUM = "minimum";
    const QString MAXIMUM = "maximum";
    const QString IN_TONNES = "in tonnes";
    const QString INTENSITY = "intensity";
    const QString INDEXED = "indexed";
    const QString INTENSITY_INDEXED = "intensity indexed";

    // Disables everything related to Statfi in UI
    void disableStatfiButtons();

    // Disables everything related to Smear in UI
    void disableSmearButtons();

    // Enables everything in UI
    void enableAllButtons();

    // Saves selections to the next time when the program is used
    void saveSelections();

    // Reads selections from file and puts them into the UI
    void readSelections();

    // Parameters:
    // - s: the string to be splitted
    // - separator: the separator that splits
    // Splits a row into smaller strings
    // and adds them to a vector of strings
    std::vector<std::string> split(const std::string& s, const char& separator,
                                   bool ignore_empty);

};
#endif // MAINWINDOW_HH
