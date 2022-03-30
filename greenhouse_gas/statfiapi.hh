#ifndef STATFIAPI_HH
#define STATFIAPI_HH

#include <QObject>
#include <QNetworkReply>

class QNetworkAccessManager;

class statfiApi : public QObject
{
    Q_OBJECT

public:
    explicit statfiApi(QObject* parent = nullptr);
    ~statfiApi();

private Q_SLOTS:
    void downloadCompleted(QNetworkReply* networkReply);

signals:
    void dataFetchedFromStatfi();

private:
    QNetworkAccessManager* manager_;
    void fetch();
};

#endif // STATFIAPI_HH
