TEMPLATE = subdirs

SUBDIRS += 	SkeletonTest \
                        CLIPPER \
                        IBK \
                        IBKMK \
                        sundials \
                        SuiteSparse \
                        SKELETON \
                        BlockMod


SkeletonTest.file = ../../SkeletonTest/projects/Qt/SkeletonTest.pro

IBK.file  = ../../externals/IBK/projects/Qt/IBK.pro
IBKMK.file  = ../../externals/IBKMK/projects/Qt/IBKMK.pro
SKELETON.file  = ../../externals/SKELETON/projects/Qt/SKELETON.pro
CLIPPER.file  = ../../externals/CLIPPER/projects/Qt/CLIPPER.pro
sundials.file = ../../externals/sundials/projects/Qt/sundials.pro
SuiteSparse.file = ../../externals/SuiteSparse/projects/Qt/SuiteSparse.pro
BlockMod.file = ../../externals/BlockMod/projects/Qt/BlockMod.pro


IBKMK.depends = IBK sundials SuiteSparse
SKELETON.depends = IBK IBKMK CLIPPER
SkeletonTest.depends = IBK IBKMK SKELETON CLIPPER BlockMod

