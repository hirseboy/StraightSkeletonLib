TEMPLATE = subdirs

SUBDIRS += 	SkeletonTest \
			SKELETON \
			IBK \
                        IBKMK \
                        CLIPPER


IBK.file  = ../../externals/IBK/projects/Qt/IBK.pro
IBKMK.file  = ../../externals/IBKMK/projects/Qt/IBKMK.pro
SKELETON.file  = ../../externals/SKELETON/projects/Qt/SKELETON.pro
CLIPPER.file  = ../../externals/CLIPPER/projects/Qt/CLIPPER.pro
SkeletonTest.file = ../../SkeletonTest/projects/Qt/SkeletonTest.pro

IBKMK.depends = IBK
SKELETON.depends = IBK IBKMK
SkeletonTest.depends = IBK IBKMK SKELETON
