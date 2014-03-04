TEMPLATE = subdirs

SUBDIRS += \
    wildstar_data \
    wildstar_package \
    wildstar_area

CONFIG( debug, debug|release ) {
    DEFINES += WILDSTAR_DEBUG
} else {
    DEFINES += WILDSTAR_NO_DEBUG
}
