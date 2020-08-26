QT       += core gui

TARGET = SkeletonTest
TEMPLATE = app

# this pri must be sourced from all our libraries,
# it contains all functions defined for casual libraries
include( ../../../externals/IBK/projects/Qt/IBK.pri )

SOURCES += \
	../../src/main.cpp


LIBS += \
		-lIBK \
		-lIBKMK \
		-lSKELETON

INCLUDEPATH = \
		../../../externals/IBK/src \
		../../../externals/IBKMK/src \
		../../../externals/SKELETON/src

HEADERS += \

