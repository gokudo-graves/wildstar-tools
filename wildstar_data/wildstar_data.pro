#-------------------------------------------------
#
# Project created by QtCreator 2014-02-28T14:50:10
#
#-------------------------------------------------

QT       -= gui

CONFIG( debug, debug|release ) {
    TARGET = wildstar_data_d
} else {
    TARGET = wildstar_data
}

TEMPLATE = lib

INCLUDEPATH += include

DEFINES += WILDSTAR_DATA_LIBRARY

SOURCES += \
    src/wildstar/data/c_package.cpp \
    src/wildstar/data/c_archive_index.cpp \
    src/wildstar/data/c_index_directory_node.cpp \
    src/wildstar/data/c_index_file_node.cpp \
    src/wildstar/data/a_index_node.cpp \
    include/wildstar/data/c_archive.cpp

HEADERS  += \
    include/wildstar/data/global.h \
    include/wildstar/data/exception.h \
    include/wildstar/data/c_package.h \
    include/wildstar/data/c_package.h \
    include/wildstar/data/c_archive_index.h \
    include/wildstar/data/c_index_directory_node.h \
    include/wildstar/data/c_index_file_node.h \
    include/wildstar/data/a_index_node.h \
    include/wildstar/data/c_archive.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
