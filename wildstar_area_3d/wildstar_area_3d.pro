#-------------------------------------------------
#
# Project created by QtCreator 2014-03-07T15:23:07
#
#-------------------------------------------------

include( common/common.pri )

TEMPLATE = app

INCLUDEPATH += common

DESTDIR = $$OUT_PWD/../out
LIBS += -L$$OUT_PWD/../out/

SOURCES += main.cpp\
    c_area_widget.cpp \
    c_area_scene.cpp \
    c_main_window.cpp

HEADERS  += \
    c_area_widget.h \
    c_area_scene.h \
    c_main_window.h

RESOURCES += wildstar_area_3d.qrc

CONFIG( debug, debug|release ) {
    TARGET = wildstar_area_3d_d
    LIBS += -lwildstar_data_d
} else {
    TARGET = wildstar_area_3d
    LIBS += -lwildstar_data
}

INCLUDEPATH += $$PWD/../wildstar_data/include
DEPENDPATH += $$PWD/../wildstar_data/include
