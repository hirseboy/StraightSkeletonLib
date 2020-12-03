QT += core
# -------------------------
# Project for SKELETON library
# -------------------------

# first we define what we are
TARGET = SKELETON
TEMPLATE = lib


# this pri must be sourced from all our libraries,
# it contains all functions defined for casual libraries
include( ../../../SKELETON/projects/Qt/IBK.pri )

# finally we setup our custom library specfic things
# like version number etc., we also may reset all
#
unix|mac {
	VER_MAJ = 1
	VER_MIN = 0
	VER_PAT = 0
	VERSION = $${VER_MAJ}.$${VER_MIN}.$${VER_PAT}
}


LIBS += -lIBK \
        -lIBKMK \
        -CLIPPER

INCLUDEPATH = \
	../../../IBK/src \
        ../../../IBKMK/src \
        ../../../CLIPPER/src

SOURCES += \
	../../src/SS_EventHandler.cpp \
	../../src/SS_Polygon.cpp

HEADERS += \
	../../src/SS_Constants.h \
	../../src/SS_EventHandler.h \
	../../src/SS_Functions.h \
	../../src/SS_Polygon.h
