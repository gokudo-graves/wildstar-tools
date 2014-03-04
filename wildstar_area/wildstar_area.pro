#-------------------------------------------------
#
# Project created by QtCreator 2014-03-04T23:13:27
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = wildstar_area
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

CONFIG( debug, debug|release ) {
    TARGET = wildstar_package_d
    LIBS += -L$$OUT_PWD/../wildstar_data/debug/ -lwildstar_data_d
} else {
    TARGET = wildstar_package
    LIBS += -L$$OUT_PWD/../wildstar_data/release/ -lwildstar_data
}

INCLUDEPATH += $$PWD/../wildstar_data/include
DEPENDPATH += $$PWD/../wildstar_data/include
