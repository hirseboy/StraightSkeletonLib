#include <string>

#include <IBK_StringUtils.h>
#include <IBK_Path.h>
#include <IBK_math.h>

#include <SS_Polygon.h>
#include <SS_Functions.h>

#include <QApplication>

#include "SkeletonGUI.h"

void makePolygons(std::vector<SKELETON::Polygon> &polys, SS_GUI &widget);

int main(int argc, char *argv[])
{
	std::vector<SKELETON::Polygon> polys;


	QApplication a(argc, argv);
	SS_GUI w;

	w.show();

	makePolygons(polys, w);

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



	SKELETON::Polygon poly(points, false);

	std::vector<SKELETON::Polygon> tempPolys;

	polys.push_back(poly);

	std::cout << "\nSTART\n";


	try {

		while ( !polys.empty() && !SKELETON::nearZero<4>( polys[0].area() ) ) {

			std::cout << "\nPoints\n";
			for (size_t j=0; j<polys[0].size(); ++j) {
				std::cout << j << "\t" << polys[0].point(j).m_x << "\t" << polys[0].point(j).m_y << std::endl;
			}

			if ( polys[0].size()>3 ) {
				tempPolys = polys[0].shrink();
				polys.insert( polys.end(), tempPolys.begin(), tempPolys.end() );
			}
			else {
				// insert empty polygon to store last Edge Point
				SKELETON::Polygon tempPoly;
				tempPoly.origins().push_back(SKELETON::Polygon::Origin ( polys[0].event(0).m_point, 0, IBKMK::Vector3D (), false ) );
				polys.insert( polys.end(), tempPoly );
			}

			std::cout << "\nOrigins\n";
			for (size_t j=0; j<polys[0].origins().size(); ++j) {
				std::cout << j << "\t" << (polys[0].origins()[j].m_isSplit ? "Split Event" : "Edge Event") << "\t" << polys[0].origins()[j].m_point.m_x << "\t" << polys[0].origins()[j].m_point.m_y << std::endl;

				SKELETON::Polygon::Origin ori = polys[0].origins()[j];

				for ( SKELETON::Polygon::Event event : polys[0].events() ) {

				IBK::Line line ( ori.m_point.toIbkPoint(),
								 ori.m_point.addVector(ori.m_vector, SKELETON::MAX_SCALE).toIbkPoint() );

				double test = SKELETON::distancePointToLine( event.m_point.toIbkPoint(), line );

				if ( IBK::nearly_equal<3>( SKELETON::distancePointToLine( event.m_point.toIbkPoint(), line ), 0.0 ) )
					 polys[0].addSkeletonLine( IBK::Line ( ori.m_point.toIbkPoint(), event.m_point.toIbkPoint() ) );
				}
			}

			std::cout << "\nSkeletons\n";
			for (size_t j=0; j<polys[0].skeletons(); ++j) {
				std::cout << j << "\t\t"    << polys[0].skeleton(j).m_p1.m_x << "\t" << polys[0].skeleton(j).m_p1.m_y << "\t\n\t\t"
						  << polys[0].skeleton(j).m_p2.m_x << "\t" << polys[0].skeleton(j).m_p2.m_y << "\t" << std::endl;
			}

			widget.drawPolygons(polys);

			polys.erase( polys.begin() );

			std::cout << "\n----------------------------------\n";
		}

	} catch (IBK::Exception &ex) {
		std::cout << ex.what();
		ex.writeMsgStackToError();
		return;
	}
	// get new Polygons, add to vector with polygons
	// if edge event happens, take new polygon, save connection and delete old
	// if split event



	for (size_t i=0; i<polys.size(); ++i) {
		std::cout << std::endl;
		for (size_t j=0; j<polys[i].size(); ++j) {
			std::cout << j << "\t" << polys[i].point(j).m_x << "\t" << polys[i].point(j).m_y << std::endl;
		}
	}

	return;
}
//#endif
