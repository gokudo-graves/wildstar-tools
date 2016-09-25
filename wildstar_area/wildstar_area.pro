#-------------------------------------------------
#
# Project created by QtCreator 2014-03-04T23:13:27
#
#-------------------------------------------------

QT       += core gui

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DESTDIR = $$OUT_PWD/../out
LIBS += -L$$OUT_PWD/../out

SOURCES += main.cpp

CONFIG( debug, debug|release ) {
    TARGET = wildstar_area_d
    LIBS += -lwildstar_data_d
} else {
    TARGET = wildstar_area
    LIBS += -lwildstar_data
}

INCLUDEPATH += $$PWD/../wildstar_data/include
DEPENDPATH += $$PWD/../wildstar_data/include
