#include <string>

#include <IBK_StringUtils.h>
#include <IBK_Path.h>
#include <IBK_math.h>

#include <SS_Polygon.h>
#include <SS_Functions.h>

#include <QApplication>
#include <QTime>

#include "SkeletonGUI.h"

void makePolygons(std::vector<SKELETON::Polygon> &polys, SS_GUI &widget);

int main(int argc, char *argv[])
{
	std::vector<SKELETON::Polygon> polys;


	QApplication a(argc, argv);
	SS_GUI w;

	w.showMaximized();
	//w.resize(1400,1000);
	try {
		// makePolygons(polys, w);
	} catch (IBK::Exception &ex) {
		ex.writeMsgStackToError();
	}

	return a.exec();
}

//#endif
