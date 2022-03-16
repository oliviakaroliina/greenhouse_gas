#ifndef SMEARAPI_HH
#define SMEARAPI_HH

#include "QNetworkAccessManager"
#include "QObject"
#include "QDebug"
#include "QNetworkReply"
#include <iostream>
#include "QNetworkRequest"


class smearApi
{
public:
    smearApi();
    void fetch();
    QNetworkAccessManager* qnam_;

};

#endif // SMEARAPI_HH
