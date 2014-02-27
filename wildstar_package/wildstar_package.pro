#-------------------------------------------------
#
# Project created by QtCreator 2014-02-26T17:38:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = wildstar_package
TEMPLATE = app


SOURCES += main.cpp\
    MainWindow.cpp \
    c_index_model.cpp \
    a_node.cpp \
    data/c_package.cpp

HEADERS  += MainWindow.h \
    c_index_model.h \
    a_node.h \
    data/c_package.h

FORMS    += MainWindow.ui
