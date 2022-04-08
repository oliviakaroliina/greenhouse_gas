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

    QVector<QString> getResponse();

signals:
    void statfiDataCollected();

private Q_SLOTS:
    void downloadCompleted(QNetworkReply* networkReply);

private:
    QNetworkAccessManager* manager_;
    MainWindow* mw_ = nullptr;
    QVector<QString> response_ = {};

    void fetch(QString start, QString end, QString coType);
    void getUsersSelections();

    int selections_ = 0;

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
