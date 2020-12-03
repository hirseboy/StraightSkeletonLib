QT += xml core gui network printsupport widgets

TARGET = SkeletonTest
TEMPLATE = app
CONFIG += console



# this pri must be sourced from all our libraries,
# it contains all functions defined for casual libraries
include( ../../../externals/IBK/projects/Qt/IBK.pri )

SOURCES += \
        ../../src/main.cpp \
        ../../src/SkeletonGUI.cpp


LIBS += \
		-lIBK \
		-lIBKMK \
                -lSKELETON \
                -lCLIPPER

INCLUDEPATH = \
		../../../externals/IBK/src \
		../../../externals/IBKMK/src \
                ../../../externals/SKELETON/src \
                ../../../externals/CLIPPER/src

HEADERS += \
                ../../src/SkeletonGUI.h

FORMS += \
                ../../src/SkeletonGUI.ui
