TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        dataHandler.cpp \
        errorHandler.cpp \
        main.cpp \
        smearApi.cpp \
        statfiApi.cpp \
        uiFrontpage.cpp \
        uiVisualize.cpp

HEADERS += \
    dataHandler.hh \
    errorHandler.hh \
    smearApi.hh \
    statfiApi.hh \
    uiFrontpage.hh \
    uiVisualize.hh
