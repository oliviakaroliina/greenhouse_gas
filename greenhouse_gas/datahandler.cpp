#include "datahandler.hh"

dataHandler::dataHandler()
{

}

void dataHandler::fetchDataFromApis()
{
    emit dataFetchedFromApis();

}
