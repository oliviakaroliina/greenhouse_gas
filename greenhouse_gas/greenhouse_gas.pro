QT       += core gui
QT += qml

QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    datahandler.cpp \
    driver.cpp \
    errorhandler.cpp \
    history.cpp \
    main.cpp \
    mainwindow.cpp \
    plotwindow.cpp \
    qcustomplot.cpp \
    smearapi.cpp \
    statfiapi.cpp \
    station.cpp

HEADERS += \
    datahandler.hh \
    driver.hh \
    errorhandler.hh \
    history.hh \
    mainwindow.hh \
    plotwindow.hh \
    qcustomplot.h \
    smearapi.hh \
    statfiapi.hh \
    station.hh

FORMS += \
    mainwindow.ui \
    plotwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=
