#ifndef STATFIAPI_HH
#define STATFIAPI_HH

#include <QNetworkReply>
#include <QObject>
#include <QString>
#include <QUrl>

class QNetworkAccessManager;

class statfiApi : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QUrl currentUrl READ getCurrentUrl NOTIFY currentUrlChanged)
    Q_PROPERTY(int currentStatuscode READ getCurrentStatuscode NOTIFY currentStatuscodeChanged)
    Q_PROPERTY(QString currentContent READ getCurrentContent NOTIFY currentContentChanged)

public:
    explicit statfiApi(QObject* parent = nullptr);
    ~statfiApi();

    QUrl getCurrentUrl() const;
    int getCurrentStatuscode() const;
    QString getCurrentContent() const;

    // HTTP request can contain multiple custom headers but support for just one in this case
    Q_INVOKABLE void requestUrlGet(const QString& url, const QString& header = "");
    Q_INVOKABLE void requestUrlPost(const QString& url, const QString& data, const QString& header = "");


private Q_SLOTS:
    void requestCompleted(QNetworkReply* networkReply);
    void requestError(QNetworkReply::NetworkError errorCode);

signals:
    void currentUrlChanged();
    void currentStatuscodeChanged();
    void currentContentChanged();

private:
    QNetworkAccessManager* network_;
    QUrl currentUrl_;
    int currentStatuscode_;
    QString currentContent_;

    void setHeader(QNetworkRequest& request, const QString& headerString);
    void connectToError(QNetworkReply* reply);
};

#endif // STATFIAPI_HH
