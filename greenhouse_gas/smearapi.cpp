#include "smearapi.hh"

smearApi::smearApi()
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

}
