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


void makePolygons(std::vector<SKELETON::Polygon> &polys, SS_GUI &widget)
{
	std::vector< IBK::point2D<double> > points;
	IBK::point2D<double> point;

#ifdef poly0
	point.set(0,0);points.push_back(point);
	point.set(0,8);points.push_back(point);
	point.set(2,8);points.push_back(point);
	point.set(2,7);points.push_back(point);
	point.set(8,7);points.push_back(point);
	point.set(8,3);points.push_back(point);
	point.set(3,3);points.push_back(point);
	point.set(3,0);points.push_back(point);
#endif

#ifdef poly1
	point.set(0,2);points.push_back(point);
	point.set(0,8);points.push_back(point);
	point.set(2,10);points.push_back(point);
	point.set(5,10);points.push_back(point);
	point.set(5.5,8);points.push_back(point);
	point.set(7,10);points.push_back(point);
	point.set(11,10);points.push_back(point);
	point.set(11,5);points.push_back(point);
	point.set(8,0);points.push_back(point);
	point.set(2,0);points.push_back(point);
#endif

#ifdef poly2
	point.set(0,0);points.push_back(point);
	point.set(1,6);points.push_back(point);
	point.set(6,6);points.push_back(point);
	point.set(6,1);points.push_back(point);
	point.set(9,6);points.push_back(point);
	point.set(8,0);points.push_back(point);
	point.set(3,0);points.push_back(point);
	point.set(3,5);points.push_back(point);
#endif

#ifdef poly3
	point.set(0,0);points.push_back(point);
	point.set(0,3);points.push_back(point);
	point.set(1,4);points.push_back(point);
	point.set(0,5);points.push_back(point);
	point.set(0,8);points.push_back(point);
	point.set(3,8);points.push_back(point);
	point.set(4,7);points.push_back(point);
	point.set(5,8);points.push_back(point);
	point.set(8,8);points.push_back(point);
	point.set(8,5);points.push_back(point);
	point.set(7,4);points.push_back(point);
	point.set(8,3);points.push_back(point);
	point.set(8,0);points.push_back(point);
	point.set(5,0);points.push_back(point);
	point.set(4,1);points.push_back(point);
	point.set(3,0);points.push_back(point);
#endif

#ifdef poly4
	point.set(0,0);points.push_back(point);
	point.set(1,4);points.push_back(point);
	point.set(0,5);points.push_back(point);
	point.set(0,7);points.push_back(point);
	point.set(1,5);points.push_back(point);
	point.set(4,4);points.push_back(point);
	point.set(4,10);points.push_back(point);
	point.set(5,11);points.push_back(point);
	point.set(8,6);points.push_back(point);
	point.set(8,0);points.push_back(point);
	point.set(3,0);points.push_back(point);
	point.set(3,3);points.push_back(point);
#endif

#ifdef poly5
	point.set(0,0);points.push_back(point);
	point.set(0,5);points.push_back(point);
	point.set(10,5);points.push_back(point);
	point.set(10,4);points.push_back(point);
	point.set(8,3.5);points.push_back(point);
	point.set(10,3);points.push_back(point);
	point.set(10,0);points.push_back(point);
	point.set(5,0);points.push_back(point);
	point.set(4,1);points.push_back(point);
	point.set(3,0);points.push_back(point);
#endif

#ifdef poly6
	point.set(0,3);points.push_back(point);
	point.set(0,6);points.push_back(point);
	point.set(1.5,6);points.push_back(point);
	point.set(1,7);points.push_back(point);
	point.set(4,7);points.push_back(point);
	point.set(4,5.5);points.push_back(point);
	point.set(5,6);points.push_back(point);
	point.set(5,3);points.push_back(point);
	point.set(3.5,3);points.push_back(point);
	point.set(4,2);points.push_back(point);
	point.set(1,2);points.push_back(point);
	point.set(1,3.5);points.push_back(point);
#endif

#ifdef poly7
	point.set(0,0);points.push_back(point);
	point.set(0,5);points.push_back(point);
	point.set(10,5);points.push_back(point);
	point.set(10,4);points.push_back(point);
	point.set(8,3.5);points.push_back(point);
	point.set(10,3);points.push_back(point);
	point.set(10,0);points.push_back(point);
	point.set(5,0);points.push_back(point);
	point.set(4,1);points.push_back(point);
	point.set(3,0);points.push_back(point);
#endif

#ifdef poly8
	point.set(0,0);points.push_back(point);
	point.set(0,8);points.push_back(point);
	point.set(2,8);points.push_back(point);
	point.set(2,7);points.push_back(point);
	point.set(8,7);points.push_back(point);
	point.set(8,3);points.push_back(point);
	point.set(3,3);points.push_back(point);
	point.set(3,0);points.push_back(point);
 #endif

#ifdef poly9
	point.set(0,0);points.push_back(point);
	point.set(0,3);points.push_back(point);
	point.set(1,4);points.push_back(point);
	point.set(0,5);points.push_back(point);
	point.set(0,8);points.push_back(point);
	point.set(3,8);points.push_back(point);
	point.set(4,7);points.push_back(point);
	point.set(5,8);points.push_back(point);
	point.set(8,8);points.push_back(point);
	point.set(8,5);points.push_back(point);
	point.set(7,4);points.push_back(point);
	point.set(8,3);points.push_back(point);
	point.set(8,0);points.push_back(point);
	point.set(5,0);points.push_back(point);
	point.set(4,1);points.push_back(point);
	point.set(3,0);points.push_back(point);
#endif

//#ifdef poly10
	point.set(0,3);points.push_back(point);
	point.set(0,6);points.push_back(point);
	point.set(1,6);points.push_back(point);
	point.set(1,7);points.push_back(point);
	point.set(4,7);points.push_back(point);
	point.set(4,6);points.push_back(point);
	point.set(5,6);points.push_back(point);
	point.set(5,3);points.push_back(point);
	point.set(4,3);points.push_back(point);
	point.set(4,2);points.push_back(point);
	point.set(1,2);points.push_back(point);
	point.set(1,3);points.push_back(point);
//#endif

#ifdef poly11
	point.set(0,0);points.push_back(point);
	point.set(0,5);points.push_back(point);
	point.set(10,5);points.push_back(point);
	point.set(10,3);points.push_back(point);
	point.set(8,2.5);points.push_back(point);
	point.set(10,2);points.push_back(point);
	point.set(10,0);points.push_back(point);
	point.set(5,0);points.push_back(point);
	point.set(4,1);points.push_back(point);
	point.set(3,0);points.push_back(point);
#endif

#ifdef poly12
	point.set(0,0);points.push_back(point);
	point.set(0,8);points.push_back(point);
	point.set(8,8);points.push_back(point);
	point.set(8,5);points.push_back(point);
	point.set(7,4);points.push_back(point);
	point.set(8,3);points.push_back(point);
	point.set(8,0);points.push_back(point);
	point.set(5,0);points.push_back(point);
	point.set(4,1);points.push_back(point);
	point.set(3,0);points.push_back(point);
#endif

	SKELETON::Polygon poly(points, false);

	poly.findSkeletonLines();
	poly.findVertexLines();

	polys.push_back(poly);
	widget.drawPolygon(poly,QPen (Qt::black, 2, Qt::SolidLine));
	widget.drawVertexLines(poly.vertexLines());


	return;
}
//#endif
