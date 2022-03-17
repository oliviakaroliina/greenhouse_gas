#include "smearapi.hh"

#include <QByteArray>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QStringList>
#include <QVariant>

/*smearApi::smearApi()
{

}

smearApi::~smearApi()
{

}

void smearApi::fetch()
{
    std::cout<< "moi";
    //auto request = QNetworkRequest(QUrl("https://smear-backend.rahtiapp.fi/search/station"));
    QNetworkRequest request;
    QString url_str = "";
    url_str.append("https://smear-backend.rahtiapp.fi/search/station");
    QUrl url;
    url.setUrl(url_str);
    request.setUrl(url);
    qnam_->get(request);
    std::cout<< qnam_;

}*/
smearApi::smearApi(QObject *parent) :
    QObject{ parent },
    network_{ new QNetworkAccessManager(this) },
    currentUrl_{ "" },
    currentStatuscode_{ 0 },
    currentContent_{ "" }
{
    // connect the "finished" signal from the network to the requestCompleted function
    connect(network_, &QNetworkAccessManager::finished, this, &smearApi::requestCompleted);
}

smearApi::~smearApi()
{
    delete network_;
}

QUrl smearApi::getCurrentUrl() const
{
    return currentUrl_;
}

int smearApi::getCurrentStatuscode() const
{
    return currentStatuscode_;
}

QString smearApi::getCurrentContent() const
{
    return currentContent_;
}

void smearApi::requestUrlGet(const QString& url, const QString& header)
{
    if (url == "")
    {
        return;
    }

    QNetworkRequest request{ url };
    setHeader(request, header);  // set the custom header with a helper function

    QNetworkReply* networkReply{ network_->get(request) };

    // NOTE: the default version uses asynchronous system so that function requestCompleted is automatically called
    // when a network request has been completed (see the constructor on how to the system is created)

    // connect an error signal for the reply to the requestError function using helper function
    // NOTE: the requestCompleted function is still also called for failed requests
    connectToError(networkReply);

    qDebug() << "GET request:" << request.url() << "headers:" << request.rawHeaderList();
}

void smearApi::requestUrlPost(const QString& url, const QString& data, const QString& header)
{
    if (url == "")
    {
        return;
    }

    QNetworkRequest request{ url };
    // set the content type header explicitly here
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    // set the custom header with a helper function
    setHeader(request, header);

    QNetworkReply* networkReply{ network_->post(request, data.toUtf8()) };

    // connect an error signal for the reply to the requestError function using helper function
    connectToError(networkReply);

    qDebug() << "POST request:" << request.url() << "headers:" << request.rawHeaderList() << "data:" << data;
}

void smearApi::requestCompleted(QNetworkReply* networkReply)
{
    // update the shown URL based on the network reply
    currentUrl_ = networkReply->url();
    emit currentUrlChanged();

    // update the shown status code based on the network reply
    QVariant statuscodeVariant{ networkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute) };
    currentStatuscode_ = statuscodeVariant.toInt();
    emit currentStatuscodeChanged();

    // get the full response from the network reply
    QByteArray responseContent{ networkReply->readAll() };
    currentContent_ = QString(responseContent);
    // normally the parsing of the response would be done here, in this case just show the raw content
    emit currentContentChanged();

    qDebug() << "Reply to" << networkReply->url() << "with status code:" << statuscodeVariant.toInt();
}

void smearApi::requestError(QNetworkReply::NetworkError errorCode)
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    qDebug() << "Received error:" << errorCode << "for url:" << reply->url();
}

void smearApi::setHeader(QNetworkRequest& request, const QString& headerString)
{
    // the header parameter is assumed to be in format "<header_name>:<header_value>"
    if (headerString != "")
    {
        QStringList headerParts{ headerString.split(":") };
        if (headerParts.length() == 2)
        {
            QString headerName{ headerParts[0] };
            QString headerValue{ headerParts[1] };
            if (headerName != "" && headerValue != "")
            {
                // set the header and its value to the request
                request.setRawHeader(headerName.toUtf8(), headerValue.toUtf8());
            }
        }
    }
}

void smearApi::connectToError(QNetworkReply* reply)
{
    connect(
        reply,
        #if (QT_VERSION >= QT_VERSION_CHECK(5, 15, 0))
            QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::errorOccurred),
        #else
            QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
        #endif
        this,
        &smearApi::requestError
    );
}


