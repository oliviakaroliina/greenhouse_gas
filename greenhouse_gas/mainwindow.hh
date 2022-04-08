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

    // Returns datatype
    // e.g. "MIN"
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

    // Returns Statfi start year
    int getStatfiStartYear();

    // Returns Statfi end year
    int getStatfiEndYear();

signals:
    void visualizeButtonPressed();

private slots:

    // Disables or enables buttons based on api choice
    void disableButtons();

    // Starts the next window
    void visualize();

    // Checks for save selections and clear all, and
    // restarts the program
    void restart();

    // Checks for save selections and clear all
    void quitButtonClicked();

private:
    Ui::MainWindow *ui;

    const std::string SELECTIONS_FILE = "selections.txt";
    const int STATFI_MEASUREMENT_START_YEAR = 1990;
    const int STATFI_MEASUREMENT_END_YEAR = 2016;

    const QString NO_VALUE = "";
    const QString SMEAR = "smear";
    const QString STATFI = "statfi";
    const QString HYYTIALA = "hyytiala";
    const QString KUMPULA = "kumpula";
    const QString VARRIO = "varrio";
    const QString CO2 = "co2";
    const QString SO2 = "so2";
    const QString NOX = "nox";
    const QString RAW = "NONE";
    const QString AVERAGE = "ARITHMETIC";
    const QString MINIMUM = "MIN";
    const QString MAXIMUM = "MAX";
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

    // Clears all selections so that the next time when program is runned,
    // it won't remember the user's previous selections.
    void clearAll();

    // Reads selections from file and puts them into the UI
    void readSelections();

    // Parameters:
    // - s: the string to be splitted
    // - separator: the separator that splits
    // Splits a row into smaller strings
    // and adds them to a vector of strings
    // Returns: a vector of strings, that has been splitted from s in spots
    //          where separators are
    std::vector<std::string> split(const std::string& s, const char& separator,
                                   bool ignoreEmpty);

    // Parameters:
    // - apis: if information to be added to UI are apis
    // - stations: if information to be added to UI are stations
    // - gases: if information to be added to UI are gases
    // - datasets: if information to be added to UI are datasets
    // - info: the information read from the file, where has been saved the user's
    //         earlier selections. e. g. {"hyytiala", "varrio"}
    // Sets different information to the UI based on the user's previous selections
    void setSelections(bool apis, bool stations, bool gases, bool datasets,
                       std::vector<std::string>& info);

    // Parameters:
    // - datatype: tells which datatype the user selected earlier
    // Sets datatype information to the UI based on the user's previous selection
    void setDatatype(std::string& datatype);

    // Parameters:
    // - smearstart: if information to be added to UI is smear's start date
    // - smearend: if information to be added to UI is smear's end date
    // - day: the day of the date to be added to the UI
    // - month: the month of the date to be added to the UI
    // - year: the year of the date to be added to the UI
    // Sets date information to the UI based on the user's previous selection
    void setDate(bool smearstart, bool smearend, int day, int month, int year);

    // Parameters:
    // - statfistart: if information to be added to UI is statfi's start year
    // - statfiend: if information to be added to UI is statfi's end year
    // - year: the year to be added to the UI
    // Sets year information to the UI based on the user's previous selection
    void setYear(bool statfistart, bool statfiend, int year);

};
#endif // MAINWINDOW_HH
