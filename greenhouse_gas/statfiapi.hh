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

private Q_SLOTS:
    void downloadCompleted(QNetworkReply* networkReply);

private:
    QNetworkAccessManager* manager_;
    void fetch();
};

#endif // STATFIAPI_HH
