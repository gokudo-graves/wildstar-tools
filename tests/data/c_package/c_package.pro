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

RESOURCES += \
    c_package.qrc
