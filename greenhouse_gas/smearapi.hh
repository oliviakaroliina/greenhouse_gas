#ifndef SMEARAPI_HH
#define SMEARAPI_HH

#include "QNetworkAccessManager"
#include "QObject"
#include "QDebug"
#include "QNetworkReply"
#include "QNetworkRequest"

class QNetworkAccessManager;

class smearApi : public QObject
{
    Q_OBJECT

public:
    explicit smearApi(QObject* parent = nullptr);
    ~smearApi();

private Q_SLOTS:
    void downloadCompleted(QNetworkReply* networkReply);

signals:
    void dataFetched();

private:
    QNetworkAccessManager* manager_;
    void fetch();
};

#endif // NETWORKHANDLER_HH
