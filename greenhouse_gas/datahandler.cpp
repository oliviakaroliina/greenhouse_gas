#include "datahandler.hh"

dataHandler::dataHandler()
{

}

void dataHandler::handleSmearData()
{
    smearDataHandled = true;
    areAllDataHandled();
}

void dataHandler::handleStatfiData()
{
    statfiDataHandled = true;
    areAllDataHandled();
}

void dataHandler::areAllDataHandled()
{
    if (smearDataHandled and statfiDataHandled)
    {
        emit dataHandled();
    }
}
