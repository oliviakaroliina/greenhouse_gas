#ifndef SMEARAPI_HH
#define SMEARAPI_HH

#include <QObject>
#include <QNetworkReply>
#include "mainwindow.hh"

class QNetworkAccessManager;

class smearApi : public QObject
{
    Q_OBJECT

public:
    explicit smearApi(QObject* parent = nullptr, MainWindow* mw = nullptr);
    ~smearApi();

    QVector<QString> getResponse();

private Q_SLOTS:
    void downloadCompleted(QNetworkReply* networkReply);

private:
    QNetworkAccessManager* manager_;
    QVector<QString> response = {};

    void fetch(QString start, QString end, QString aggregation,
               QString gas_station);

    void getParameters(MainWindow* mw);

    const QString VARRIO = "varrio";
};

#endif // NETWORKHANDLER_HH
