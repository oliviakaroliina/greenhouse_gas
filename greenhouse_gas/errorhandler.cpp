#include "errorhandler.hh"
#include "mainwindow.hh"
#include <iostream>
#include <QTime>
#include <QDebug>

errorHandler::errorHandler(MainWindow *mw)
{
    mw_ = mw;
}

QString errorHandler::checkErrors()
{
    QDate smearStart = mw_->getSmearStartDate();
    QDate smearEnd = mw_->getSmearEndDate();
    int statfiStart = mw_->getStatfiStartYear();
    int statfiEnd = mw_->getStatfiEndYear();
    QDate current_date = QDate::currentDate();

    QVector<QString> apis = mw_->getApis();

    // The user has not chosen all the needed parts
    if (apis.empty()) {
        return "The place to collect the data is not chosen";
    }
    else {
        if (std::find(apis.begin(), apis.end(), "smear") != apis.end() or
            apis.length() == 2) {
            if (mw_->getMonitoringStations().empty()) {
                return "The station is not chosen";
            }
            if (mw_->getGreenhouseGases().empty()) {
                return "The gas is not selected";
            }
            if (mw_->getDatatype() == "") {
                return "The datatype is not selected";
            }
        }
        if (std::find(apis.begin(), apis.end(), "statfi") != apis.end() or
            apis.length() == 2) {
            if (mw_->getDatasets().empty()) {
                return "The dataset has not been chosen";
            }
        }
    }
    // SMEAR dates are in the future
    if (smearStart > current_date or smearEnd > current_date) {
        return "At least one of the chosen dates is in the future";
    }
    // SMEAR dates are too far in the past
    if (smearStart.year() < 2005 or smearEnd.year() < 2005) {
        return "The dates have to be in year 2005 or newer";
    }
    // SMEAR start date is newer than the end date
    if (smearStart > smearEnd) {
        return "The start date is newer than the end date";
    }
    // STATFI end year is smaller than start year
    if (statfiEnd < statfiStart) {
        return "The start year is newer than the end year";
    }
    return "No errors";
}
