#ifndef SMEARAPI_HH
#define SMEARAPI_HH

#include <QObject>
#include <QNetworkReply>

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
    void dataFetchedFromSmear();

private:
    QNetworkAccessManager* manager_;
    void fetch();
};

#endif // NETWORKHANDLER_HH
