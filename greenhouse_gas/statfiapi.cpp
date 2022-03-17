
#include "statfiapi.hh"
#include <QByteArray>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QStringList>
#include <QVariant>
#include <iostream>

statfiApi::statfiApi(QObject *parent) :
    QObject{ parent },
    network_{ new QNetworkAccessManager(this) },
    currentUrl_{ "" },
    currentStatuscode_{ 0 },
    currentContent_{ "" }
{
    // connect the "finished" signal from the network to the requestCompleted function
    connect(network_, &QNetworkAccessManager::finished, this, &statfiApi::requestCompleted);
}

statfiApi::~statfiApi()
{
    delete network_;
}

QUrl statfiApi::getCurrentUrl() const
{
    return currentUrl_;
}

int statfiApi::getCurrentStatuscode() const
{
    return currentStatuscode_;
}

QString statfiApi::getCurrentContent() const
{
    return currentContent_;
}

void statfiApi::requestUrlGet(const QString& url, const QString& header)
{
    if (url == "")
    {
        return;
    }

    QNetworkRequest request{ url };
    setHeader(request, header);
    QNetworkReply* networkReply{ network_->get(request) };
    connectToError(networkReply);
    qDebug() << "GET request:" << request.url() << "headers:" << request.rawHeaderList();

}

void statfiApi::requestUrlPost(const QString& url, const QString& data, const QString& header)
{
    if (url == "")
    {
        return;
    }

    QNetworkRequest request{ url };
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    setHeader(request, header);

    QNetworkReply* networkReply{ network_->post(request, data.toUtf8()) };
    connectToError(networkReply);

    qDebug() << "POST request:" << request.url() << "headers:" << request.rawHeaderList() << "data:" << data;
}

void statfiApi::requestCompleted(QNetworkReply* networkReply)
{
    currentUrl_ = networkReply->url();
    emit currentUrlChanged();

    QVariant statuscodeVariant{ networkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute) };
    currentStatuscode_ = statuscodeVariant.toInt();
    emit currentStatuscodeChanged();

    QByteArray responseContent{ networkReply->readAll() };
    currentContent_ = QString(responseContent);
    emit currentContentChanged();

    qDebug() << "Reply to" << networkReply->url() << "with status code:" << statuscodeVariant.toInt();
}

void statfiApi::requestError(QNetworkReply::NetworkError errorCode)
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    qDebug() << "Received error:" << errorCode << "for url:" << reply->url();
}

void statfiApi::setHeader(QNetworkRequest& request, const QString& headerString)
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
                request.setRawHeader(headerName.toUtf8(), headerValue.toUtf8());
            }
        }
    }
}

void statfiApi::connectToError(QNetworkReply* reply)
{
    connect(
        reply,
        #if (QT_VERSION >= QT_VERSION_CHECK(5, 15, 0))
            QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::errorOccurred),
        #else
            QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
        #endif
        this,
        &statfiApi::requestError
    );
}
