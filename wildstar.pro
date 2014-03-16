TEMPLATE = subdirs

SUBDIRS += \
    wildstar_data \
    wildstar_package \
    wildstar_area \
    wildstar_area_3d

CONFIG( debug, debug|release ) {
    DEFINES += WILDSTAR_DEBUG
} else {
    DEFINES += WILDSTAR_NO_DEBUG
}
