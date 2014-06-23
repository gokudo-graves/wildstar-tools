#-------------------------------------------------
#
# Project created by QtCreator 2014-06-20T10:28:46
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = test_c_package
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += test_c_package.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

include( $$common_pri )

#CONFIG( debug, debug|release ) {
#    LIBS += -L$$PWD/../../../wildstar_data/debug/ -lwildstar_data_d
#} else {
#    LIBS += -L$$PWD/../../../wildstar_data/release/ -lwildstar_data
#}
#
#INCLUDEPATH += $$PWD/../../../wildstar_data/include
#DEPENDPATH += $$PWD/../../../wildstar_data/include

RESOURCES += \
    test_files.qrc
