TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        data_handler.cpp \
        error_handler.cpp \
        main.cpp \
        smear_api.cpp \
        statfi_api.cpp \
        ui_frontpage.cpp \
        ui_visualize.cpp

HEADERS += \
    data_handler.hh \
    error_handler.hh \
    smear_api.hh \
    statfi_api.hh \
    ui_frontpage.hh \
    ui_visualize.hh
