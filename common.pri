CONFIG( debug, debug|release ) {
    LIBS += -L$$top_srcdir/build/wildstar_data/debug/ -lwildstar_data_d
} else {
    LIBS += -L$$top_builddir/build/wildstar_data/release/ -lwildstar_data
}

CONFIG += c++11

INCLUDEPATH += $$top_srcdir/wildstar_data/include
DEPENDPATH += $$top_srcdir/wildstar_data/include
