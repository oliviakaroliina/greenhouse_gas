#ifndef STATFIAPI_HH
#define STATFIAPI_HH

#include <QObject>
#include <QNetworkReply>
#include "mainwindow.hh"

class QNetworkAccessManager;

class statfiApi : public QObject
{
    Q_OBJECT

public:
    explicit statfiApi(QObject* parent = nullptr, MainWindow* mw = nullptr);
    ~statfiApi();

    // Returns a response from post-request to api
    QVector<QString> getResponse();

signals:
    // Signals when data is collected from the api
    void statfiDataCollected();

private Q_SLOTS:
    // Download completed
    void downloadCompleted(QNetworkReply* networkReply);

private:
    // Manages the post-request from api
    QNetworkAccessManager* manager_;

    // Saves the user's choises in mainwindow UI
    MainWindow* mw_ = nullptr;

    // Saves the response to QVector
    QVector<QString> response_ = {};

    /* Parameters:
     * start: user's choise for the start year
     * end: user's choise for the end year
     * coType: user's choise(s) for the CO2-type(s)
     * */
    void fetch(QString start, QString end, QString coType);

    // Fetches the user's selections from mainWindow
    void getUsersSelections();

    // Saves the amount of selections made
    int selections_ = 0;

    // Variables for co types
    const QString IN_TONNES = "in tonnes";
    const QString INTENSITY = "intensity";
    const QString INDEXED = "indexed";
    const QString INTENSITY_INDEXED = "intensity indexed";
    const QString API_IN_TONNES = "Khk_yht";
    const QString API_INTENSITY = "Khk_yht_las";
    const QString API_INDEXED = "Khk_yht_index";
    const QString API_INTENSITY_INDEXED = "Khk_yht_las_index";
};

#endif // STATFIAPI_HH
