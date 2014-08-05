#-------------------------------------------------
#
# Project created by QtCreator 2014-02-26T17:38:56
#
#-------------------------------------------------

QT       += core network
QT       -= gui

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DESTDIR = $$OUT_PWD/../out

SOURCES += main.cpp\
    command/c_command_map.cpp \
    command/c_extract.cpp \
    command/c_list.cpp \
    command/c_patch.cpp \
    command/patch/c_version.cpp \
    c_application.cpp

HEADERS  += \
    command/i_command.h \
    command/c_command_map.h \
    command/c_extract.h \
    command/c_list.h \
    command/c_patch.h \
    command/patch/c_version.h \
    c_application.h

CONFIG( debug, debug|release ) {
    TARGET = wildstar_package_d
    LIBS += -L$$OUT_PWD/../wildstar_data/debug/ -lwildstar_data_d
} else {
    TARGET = wildstar_package
    LIBS += -L$$OUT_PWD/../wildstar_data/release/ -lwildstar_data
}

INCLUDEPATH += $$PWD/../wildstar_data/include
DEPENDPATH += $$PWD/../wildstar_data/include
