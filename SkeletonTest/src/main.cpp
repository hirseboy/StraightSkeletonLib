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

	w.show();
	w.resize(1400,1000);
	try {
		makePolygons(polys, w);
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


	SKELETON::Polygon poly(points, false);

	std::vector<SKELETON::Polygon> tempPolys;

	polys.push_back(poly);

	std::cout << "\nSTART\n";

	widget.m_draw = true;

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
				// set events
				polys[0].set(true);

				// insert empty polygon to store last Edge Point
				SKELETON::Polygon tempPoly;
				tempPoly.origins().push_back(SKELETON::Polygon::Origin ( polys[0].event(0).m_point, 0, IBKMK::Vector3D (), false ) );
				polys.insert( polys.end(), tempPoly );

			}

			std::cout << "\nOrigins\n";
			for (size_t j=0; j<polys[0].origins().size(); ++j) {
				std::cout << j
						  << "\t" << (polys[0].origins()[j].m_isSplit ? "Split Event\n" : "Edge Event\n")
						<< "\t" << polys[0].origins()[j].m_point.m_x << "\t" << polys[0].origins()[j].m_point.m_y << std::endl;

				SKELETON::Polygon::Origin ori = polys[0].origins()[j];

				//				for ( SKELETON::Polygon::Event event : polys[0].events() ) {
				for ( size_t k=0; k< polys[0].events().size(); k++) {

					IBK::Line line ( ori.m_point.toIbkPoint(),
									 ori.m_point.addVector(ori.m_vector, SKELETON::MAX_SCALE).toIbkPoint() );

					//					double test = SKELETON::distancePointToLine( event.m_point.toIbkPoint(), line );


					// test weather event point lies on bisector line from origin
					// if a inherited polygon exists we hav to take the edge point of it
					if ( k == 0 || IBK::nearly_equal<3>( polys[0].events()[k].m_distanceToLine, polys[0].events()[k-1].m_distanceToLine ) ) {
						if ( IBK::nearly_equal<3>( SKELETON::distancePointToLine( polys[0].events()[k].m_point.toIbkPoint(), line ), 0.0 ) ) {
							polys[0].addSkeletonLine( IBK::Line ( ori.m_point.toIbkPoint(), polys[0].events()[k].m_point.toIbkPoint() ) );
						}
					}
					else
						break;
				}
			}

			std::cout << "\nSkeletons\n";
			for (size_t j=0; j<polys[0].skeletons(); ++j) {
				std::cout << j << "\t\t"    << polys[0].skeleton(j).m_p1.m_x << "\t" << polys[0].skeleton(j).m_p1.m_y << "\t\n\t\t"
						  << polys[0].skeleton(j).m_p2.m_x << "\t" << polys[0].skeleton(j).m_p2.m_y << "\t" << std::endl;
			}

			widget.drawPolygons(polys);

			QTime dieTime= QTime::currentTime().addSecs(1);
			while (QTime::currentTime() < dieTime)
				QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

			polys.erase( polys.begin() );

			// check for area
			std::vector<size_t> delPolys;
			for ( size_t l=0; l<polys.size(); ++l ) {
				if ( IBK::nearly_equal<4>( polys[l].area(), 0 ) ) {
					delPolys.push_back(l);
				}
			}
			for ( size_t l=delPolys.size(); l>0; --l )
				polys.erase( polys.begin()+delPolys[l-1] );

			polys[0].checkSanity();

			std::cout << "\n----------------------------------\n";
		}

	} catch (IBK::Exception &ex) {
		std::cout << ex.location() << "\t" << ex.what() << "\t";
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
