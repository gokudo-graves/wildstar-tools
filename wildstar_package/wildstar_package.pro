#-------------------------------------------------
#
# Project created by QtCreator 2014-02-26T17:38:56
#
#-------------------------------------------------

QT       += core
QT       -= gui

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DESTDIR = $$OUT_PWD/../out

SOURCES += main.cpp\
    c_list_command.cpp \
    c_extract_command.cpp

HEADERS  += \
    i_command.h \
    c_list_command.h \
    c_extract_command.h

CONFIG( debug, debug|release ) {
    TARGET = wildstar_package_d
    LIBS += -L$$OUT_PWD/../wildstar_data/debug/ -lwildstar_data_d
} else {
    TARGET = wildstar_package
    LIBS += -L$$OUT_PWD/../wildstar_data/release/ -lwildstar_data
}

INCLUDEPATH += $$PWD/../wildstar_data/include
DEPENDPATH += $$PWD/../wildstar_data/include
