#-------------------------------------------------
#
# Project created by QtCreator 2014-03-07T15:23:07
#
#-------------------------------------------------

QT       += opengl widgets

TEMPLATE = app

SOURCES += main.cpp\
    c_area_widget.cpp \
    c_main_window.cpp

HEADERS  += \
    c_area_widget.h \
    c_main_window.h

CONFIG( debug, debug|release ) {
    TARGET = wildstar_area_3d_d
    LIBS += -L$$OUT_PWD/../wildstar_data/debug/ -lwildstar_data_d
} else {
    TARGET = wildstar_area_3d
    LIBS += -L$$OUT_PWD/../wildstar_data/release/ -lwildstar_data
}

INCLUDEPATH += $$PWD/../wildstar_data/include
DEPENDPATH += $$PWD/../wildstar_data/include
