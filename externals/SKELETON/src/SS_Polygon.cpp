#include "SS_Polygon.h"
#include "SS_Constants.h"
#include "SS_Functions.h"

#include <math.h>
#include <cmath>

#include <IBK_assert.h>
#include <IBK_Line.h>
#include <IBK_messages.h>

#include <clipper.hpp>


namespace SKELETON {

Polygon::Polygon(const std::vector<IBK::point2D<double> > &points, bool setEvents)
{
	for (size_t i=0; i<points.size(); ++i) {
		m_points.push_back(Point(points[i]));
	}
	if (!set(setEvents))
		throw IBK::Exception(IBK::FormatString("Polygon could not be initialized."), "[Polygon::Polygon]");
}

Polygon::~Polygon()
{
	m_points.clear();
	m_bisectors.clear();
	m_lines.clear();
	m_lineVectors.clear();
}

bool Polygon::set(bool setEvents)
{
	if (!setVectors())
		throw IBK::Exception(IBK::FormatString("Vectors could not be initialized.\n"), "[Polygon::set]");
	if (!setBisectors())
		throw IBK::Exception(IBK::FormatString("Bisectors could not be initialized.\n"), "[Polygon::set]");
	if (!setLines())
		throw IBK::Exception(IBK::FormatString("Lines could not be initialized.\n"), "[Polygon::set]");
	if (!setArea())
		throw IBK::Exception(IBK::FormatString("Area could not be initialized.\n"), "[Polygon::set]");
	if (setEvents) {
		setSplitEventsBisector();
		setSplitEventsTrianlge();
		setEdgeEvents();
		std::cout << "\nEvents\n";
		if ( m_events.size()>0 ) {
			for ( int i=0; i<m_events.size(); ++i)
				std::cout << ( m_events[i].m_isSplit ? "Split" : "Edge" ) << "\t" << m_events[i].m_point.m_x << "\t" << m_events[i].m_point.m_y << "\t" << m_events[i].m_distanceToLine << std::endl;
			std::cout << std::endl;
		}

		// go through all events if we find events with same size
		if ( m_events.size()>1 ){
			for ( size_t k=0; k<m_events.size()-1; ++k ) {
				if ( m_events[0].m_isSplit )
					break;
				if ( IBK::nearly_equal<3>(m_events[0].m_distanceToLine, m_events[k+1].m_distanceToLine) ) {
					if ( SKELETON::checkPoints<3>(  m_events[k].m_point.toIbkPoint(), m_events[k+1].m_point.toIbkPoint() ) ) {
						IBK::IBK_Message("Event Points have the same Coordinates", IBK::MSG_WARNING, "[Polygon::set]" );
						continue;
					}
					IBK::Line line ( m_events[k].m_point.toIbkPoint(), m_events[k+1].m_point.toIbkPoint() );
					addSkeletonLine( line );
				}
				else
					break;
			}
		}
	}


	return true;
}

bool Polygon::setBisectors()
{
	m_bisectors.clear();

	size_t iB;
	int sgn=1;

	if ( !isClockwise() )
		sgn=-1;

	for(size_t i=0; i<size(); ++i)
	{
		iB = modMinus(i, size());
		IBKMK::Vector3D vBisector = m_lineVectors[i] - m_lineVectors[iB];
		vBisector.normalize();

		// check wheather the point is a convex point
		convex(i) ? vBisector=-1*vBisector : vBisector;

		m_bisectors.push_back(sgn*vBisector);
	}
	return true;
}

bool Polygon::setVectors()
{
	m_lineVectors.clear();

	size_t iN;
	for (size_t i=0; i<size(); ++i) {
		iN = modPlus(i,size());
		// first store points that need to be deleted
		m_lineVectors.push_back( SKELETON::vector(m_points[iN], m_points[i], true) );
	}
	return true;
}

bool Polygon::setLines()
{
	m_lines.clear();

	size_t iN;
	for (size_t i=0; i<size(); ++i) {
		iN = modPlus(i,size());
		// first store points that need to be deleted
		m_lines.push_back( IBK::Line(m_points[i].toIbkPoint(), m_points[iN].toIbkPoint()) );
		IBKMK::Vector3D v = m_points[i].toIbkVector3D() - m_points[iN].toIbkVector3D();
		m_lineLengths.push_back( v.magnitude() );
	}
	return true;
}

bool Polygon::setEdgeEvents()
{
	if(m_points.empty())
		throw IBK::Exception(IBK::FormatString("Points of Polygon are not set.\n"), "[Polygon::setEdgeEvents]");

	for (size_t i=0; i<m_points.size(); ++i)
	{
		Point p;
		if ( !bisectorIntersection(i, p) ) {
			IBK::IBK_Message( IBK::FormatString("Did not find an Intersection point for Line Segment with Index %1\n").arg(i), IBK::MSG_WARNING, "[Polygon::setEdgeEvents]", IBK::VL_ALL );
			continue;
		}

		double d = distancePointToLine(p.toIbkPoint(), m_lines[i]);
		// if distToLine is NaN set it to 0.0
		d = (d != d) ? 0.0 : d;

		if ( pointInPolygon(p, m_points) ) {
			// check that there is no doubling in Edge Event Points
			bool inList = false;
			for(size_t j=0; j<m_events.size(); ++j) {
				if (checkPoints<4>(p, m_events[j].m_point) && IBK::nearly_equal<4>(d,m_events[j].m_distanceToLine) && !m_events[j].m_isSplit) {
					inList = true;
					m_events[j].m_pointsEdge.push_back(i);
				}
			}
			if (!inList) {
				if( !pointOnPoint<3>(p.toIbkPoint() ) )
					addEvent(Event (p, d, std::vector<size_t>(0), std::vector<size_t>(1,i), false, false));
			}
		}
	}
	sortEvents();
	return true;
}

bool Polygon::setSplitEventsTrianlge()
{
	// this algorithm is kind of difficult and needs further adjustment
	// 1.: go through all points
	// 2.: find if the point is convex
	// 3.: if point is convex find a corresbonding line to get the split Event.
	// 4.: check wether split event lies in polygon
	// 5.: if true add it to the list
	// 6.: check next lines, if we find a split event with shorter distance, then add it also

	bool splitEvents = false;

	if ( m_lineVectors.size() != size())
		throw IBK::Exception(IBK::FormatString("Vectors and Points Sizes do not match.\n"), "[Polygon::convex]");

	if ( m_lines.size() != size())
		throw IBK::Exception(IBK::FormatString("Lines and Points Sizes do not match.\n"), "[Polygon::convex]");

	size_t iB, iS;
	IBK::point2D<double> p1, p2;

	// go through all polygon points
	for (size_t i=0; i<size(); ++i) {

		// check the convexity
		if ( convex(i) ) {
			for (size_t j=0; j<size()-2; ++j) {
				iB = modMinus(i,size());

				iS = modPlus(i+j,size());
				// take negative Vectors from convex Point we found to draw lines
				IBK::Line l1 ( m_points[i].addVector(m_lineVectors[i],-MAX_SCALE).toIbkPoint(), m_points[i].toIbkPoint());
				IBK::Line l2 ( m_points[i].addVector(m_lineVectors[iB],MAX_SCALE).toIbkPoint(), m_points[i].toIbkPoint());

				// line of opposite Line Segment
				IBK::Line lS ( m_points[iS].addVector(m_lineVectors[iS],MAX_SCALE).toIbkPoint(), m_points[iS].addVector(m_lineVectors[iS],-1*MAX_SCALE).toIbkPoint());

				double d = distancePointToLine(m_points[i].toIbkPoint(), m_lines[iS]);

				bool testl1 = l1.intersects(lS,p1);
				bool testl2 = l2.intersects(lS,p2);

				if ( !IBK::nearly_equal<4>(d,0.0) && l1.intersects(lS,p1) && l2.intersects(lS,p2) ){
					Point point1 (p1);
					Point point2 (p2);
					Point pCenter;

					// still a bit russian unfortunatly
					std::vector< IBK::point2D<double> > points;
					points.push_back(m_points[i].toIbkPoint());
					points.push_back(p2);
					points.push_back(p1);

					Polygon triangle (points, false);

					if ( !triangle.checkSanity<3>() )
						continue;

					if ( triangleCenter(m_points[i], point2, point1, pCenter) ) {
						if ( pointInPolygon(pCenter, m_points)) {

							if (triangle.m_lineLengths.empty() || triangle.m_lineLengths.size() < 3)
								throw IBK::Exception(IBK::FormatString("Line Lengths of Triangle are not set."), "Polygon::setSplitEvents") ;

							double dSplit = 2*triangle.area()/( triangle.m_lineLengths[0] + triangle.m_lineLengths[1] + triangle.m_lineLengths[2] );
							// go through events to avoid ambuigity
							bool inList = false;
							for ( size_t k=0; k<m_events.size(); ++k ) {
								if (checkPoints<4>(pCenter, m_events[k].m_point) && IBK::nearly_equal<4>(d,m_events[k].m_distanceToLine) && m_events[k].m_isSplit) {
									inList = true;
									m_events[k].m_linesSplit.push_back(i);
								}
							}
							if (!inList) {
								addEvent(Event (pCenter, dSplit, std::vector<size_t>(1,i),std::vector<size_t>(0),false, true));
								splitEvents = true;
							}
						}
					}
				}
			}
		}
	}
	sortEvents();
	return splitEvents;
}

bool Polygon::setSplitEventsBisector()
{
	bool splitEvents = false;

	if ( m_lineVectors.size() != size())
		throw IBK::Exception(IBK::FormatString("Vectors and Points Sizes do not match.\n"), "[Polygon::convex]");

	if ( m_lines.size() != size())
		throw IBK::Exception(IBK::FormatString("Lines and Points Sizes do not match.\n"), "[Polygon::convex]");

	size_t iB, iS;
	std::vector< IBK::point2D<double> > intersectionPoints;
	IBK::point2D<double> pI;

	// go through all polygon points
	for (size_t i=0; i<size(); ++i) {

		// check the convexity
		if ( convex(i) ) {

			iB = modMinus(i,size());
			// check all polygon lines
			std::vector< splitPoint > splitPoints;
			splitPoints.push_back(splitPoint ());
			splitPoints.push_back(splitPoint ());

			intersectionPoints.push_back( IBK::point2D<double> () );
			intersectionPoints.push_back( IBK::point2D<double> () );


			// take negative Vectors from convex Point we found to draw lines
			splitPoints[0].m_line = IBK::Line ( m_points[i].addVector(m_lineVectors[i],-MAX_SCALE).toIbkPoint(), m_points[i].toIbkPoint() );
			splitPoints[1].m_line = IBK::Line ( m_points[i].addVector(m_lineVectors[iB],MAX_SCALE).toIbkPoint(), m_points[i].toIbkPoint() );

			for (size_t j=0; j<size()-2; ++j) {

				iS = modPlus(i+j,size());

				// line of opposite Line Segment
				//				IBK::Line lS ( m_points[iS].addVector(m_lineVectors[iS],MAX_SCALE).toIbkPoint(), m_points[iS].addVector(m_lineVectors[iS],-1*MAX_SCALE).toIbkPoint());
				IBK::Line lS ( m_lines[iS] );

				double d = distancePointToLine(m_points[i].toIbkPoint(), m_lines[iS]);

				splitPoints[0].m_intersected = splitPoints[0].m_line.intersects(lS,intersectionPoints[0]);
				splitPoints[1].m_intersected = splitPoints[1].m_line.intersects(lS,intersectionPoints[1]);

				splitPoints[0].m_splitPoint = intersectionPoints[0];
				splitPoints[1].m_splitPoint = intersectionPoints[1];


				SKELETON::Polygon::Point p;

				if ( !splitPoints[0].m_intersected && !splitPoints[1].m_intersected )
					continue;

				bool addPoint=true;
				// if intersect point is a point of polygon break
				for ( size_t k=0; k<splitPoints.size(); ++k ) {

					if ( !splitPoints[k].m_intersected )
						continue;

					splitPoints[k].m_bisectorLine = IBK::Line ( m_points[i].addVector(m_bisectors[i],MAX_SCALE).toIbkPoint(),
																m_points[i].toIbkPoint() );

					IBK::Line lSlong ( m_points[iS].addVector(m_lineVectors[iS],-MAX_SCALE).toIbkPoint(),
									   m_points[iS].addVector(m_lineVectors[iS],MAX_SCALE).toIbkPoint() );

					splitPoints[k].m_bisectorIntersected = splitPoints[k].m_bisectorLine.intersects(lSlong,pI);

					splitPoints[k].m_bisectorLine = IBK::Line ( m_points[i].toIbkPoint(),
																m_points[i].addVector(m_bisectors[i], MAX_SCALE).toIbkPoint() );

					Polygon triangle;
					IBKMK::Vector3D vec;

					triangle << m_points[i];
					if ( k==1 && m_clockwise ) {
						triangle << splitPoints[k].m_splitPoint;
						triangle << pI;

						if ( !triangle.checkSanity<3>() )
							continue;

						triangle.set(false);

						vec = triangle.m_bisectors[1];
					} else {
						triangle << pI;
						triangle << splitPoints[k].m_splitPoint;

						if ( !triangle.checkSanity<3>() )
							continue;

						triangle.set(false);

						vec = triangle.m_bisectors[2];
					}

					Point p;
					p = m_points[i];

					IBKMK::Vector3D vecBisector ( intersectionPoints[k].m_x - m_points[i].toIbkPoint().m_x,
												  intersectionPoints[k].m_y - m_points[i].toIbkPoint().m_y,
												  0.0);

					IBKMK::Vector3D vector ( pI.m_x - m_points[i].m_x,
											 pI.m_y - m_points[i].m_y,
											 0.0);

					IBK::Line lTriangle ( splitPoints[k].m_splitPoint.toIbkPoint(),
										  splitPoints[k].m_splitPoint.addVector(vec, MAX_SCALE).toIbkPoint());

					IBK::point2D<double> point;

					splitPoints[k].m_bisectorLine.intersects( lTriangle, point );

					double distance = 0.5*vecBisector.magnitude();

					// check that split point is not already listed
					for ( size_t i=0; i<m_events.size(); ++i ) {
						if ( SKELETON::checkPoints<4>( point, m_events[i].m_point ) && ( distance != m_events[i].m_distanceToLine ) )
							addPoint = false; break;
					}

					// check that split point lies inside polygon
					if ( !SKELETON::pointInPolygon(point, m_points) )
						addPoint = false;

					if ( addPoint ) {
						addEvent( Event ( point, distance, iS, 0, false, true ) );
					}



				}
			}
		}
	}

	sortEvents();
	return splitEvents;
}

bool Polygon::setArea()
{
	if(m_points.empty())
		throw IBK::Exception(IBK::FormatString("Points of Polygon are not set.\n"), "[Polygon::area]");

	double area = 0.0;
	for (size_t i=0; i<size(); ++i)
	{
		size_t iN = modPlus(i,size());
		area += 0.5 * (m_points[i].m_x*m_points[iN].m_y - m_points[iN].m_x*m_points[i].m_y);
	}
	m_area = std::abs(area);
	return true;
}

bool Polygon::convex(const size_t & pointIdx)
{
	if ( m_lineVectors.empty())
		throw IBK::Exception(IBK::FormatString("Vectors of Polygon are not set.\n"), "[Polygon::convex]");

	if ( m_lineVectors.size() != size())
		throw IBK::Exception(IBK::FormatString("Vectors and Points Sizes do not math.\n"), "[Polygon::convex]");

	double aB, aA, aDiff;
	size_t iB;

	iB = modMinus(pointIdx, size());

	aA = std::atan2(m_lineVectors[pointIdx].m_x,m_lineVectors[pointIdx].m_y);
	aA =(aA < 0) ? (aA + 2*PI) : aA;

	aB = std::atan2(-m_lineVectors[iB].m_x,-m_lineVectors[iB].m_y);
	aB =(aB < 0) ? (aB + 2*PI) : aB;

	aDiff = aB - aA;
	aDiff = (aDiff<0) ? (aDiff + 2*PI) : aDiff;

	double testaA = aA / DEG_TO_RAD;
	double testaB = aB / DEG_TO_RAD;
	double test = aDiff / DEG_TO_RAD;

	//if (IBK::nearly_equal<4>(aDiff,2*PI) || IBK::nearly_equal<4>(aDiff,0.0) )
	// return false;
	if ( (aDiff>PI && m_clockwise) || (aDiff<PI && !m_clockwise) )
		return true;
	return false;
}

bool Polygon::bisectorIntersection(const size_t & lineIdx, Polygon::Point & p)
{
	if(lineIdx > m_points.size())
		throw IBK::Exception(IBK::FormatString("Line Index out of Range. Maximum Size is %1\n").arg(m_points.size()), "[Polygon::bisectorIntersection]");

	if(m_bisectors.empty())
		throw IBK::Exception(IBK::FormatString("Bisectors are not set in Polygon.\n"), "[Polygon::bisectorIntersection]");

	IBK_ASSERT(m_points.size() == m_bisectors.size())

			size_t iN, i;
	iN = modPlus(lineIdx, size());

	Point p1 = m_points[iN].addVector(m_bisectors[iN], SKELETON::MAX_SCALE);
	Point p2 = m_points[lineIdx].addVector(m_bisectors[lineIdx], SKELETON::MAX_SCALE);

	IBK::Line l1 ( m_points[iN].toIbkPoint(), p1.toIbkPoint() );
	IBK::Line l2 ( m_points[lineIdx].toIbkPoint(), p2.toIbkPoint() );

	IBK::point2D<double> point;
	if (!l1.intersects(l2,point))
		IBK::IBK_Message(IBK::FormatString("Line 1 does not intersect Line 2"),IBK::MSG_WARNING, "[Polygon::bisectorIntersection]", IBK::VL_ALL);
	p = Point (point);

	return true;
}

template <size_t digits>
bool Polygon::pointOnPoint(const IBK::point2D<double> &point)
{
	bool onPoint=false;
	for (size_t i=0; i<size(); ++i)
		if( checkPoints<digits>( point, m_points[i] ) )
			onPoint=!onPoint;
	return onPoint;
}

template <size_t digits>
bool Polygon::pointOnLine(const IBK::point2D<double> &point)
{
	size_t iN;
	IBK::Line line;
	for (size_t i=0; i<size(); ++i)
		if (SKELETON::pointOnLine<digits>(point, m_lines[i]))
			return true;
	return false;
}

size_t Polygon::size() const
{
	if(m_points.empty())
		throw IBK::Exception(IBK::FormatString("Points of Polygon are not set.\n"), "[Polygon::size]");


	return (int)m_points.size();

}


bool Polygon::isClockwise()
{
	double sum = 0.0;
	for (int i = 0; i < size(); ++i) {
		IBK::point2D<double> v1 = m_points[i].toIbkPoint() ;
		IBK::point2D<double> v2 = m_points[(i + 1) % size()].toIbkPoint();
		sum += (v2.m_x - v1.m_x) * (v2.m_y + v1.m_y);
	}
	return sum > 0.0;
}


IBKMK::Vector3D Polygon::bisector(const size_t &bisectorIdx)
{
	if(bisectorIdx > m_bisectors.size())
		throw IBK::Exception(IBK::FormatString("Bisector Index out of Range. Maximum Size is %1\n").arg(m_bisectors.size()), "[Polygon::bisector]");

	return m_bisectors[bisectorIdx];
}

double Polygon::distanceToLine(const size_t &pointIdx)
{
	return 0.0;
}

std::vector<Polygon> Polygon::shrink()
{
	set(true);

	if (m_events.empty())
		throw IBK::Exception( IBK::FormatString("Events not set.\n"), "[Polygon::shrink]");

	sortEvents();

	// if points are the same take edge event
	for ( size_t i=1; i<m_events.size(); ++i ) {
		if ( SKELETON::checkPoints<3>( m_events[i].m_point, m_events[i-1].m_point ) &&
			 m_events[i-1].m_isSplit && !m_events[i].m_isSplit)
			m_events[i-1].m_isSplit = false;
		else if ( ( m_events[i-1].m_isSplit && !m_events[i].m_isSplit ) &&
				  IBK::nearly_equal<3>( m_events[i].m_distanceToLine, m_events[i-1].m_distanceToLine ) ) {
			addSkeletonLine( IBK::Line(m_events[i-1].m_point.toIbkPoint(), m_events[i].m_point.toIbkPoint() ) );
		} else
			break;
	}

	// now we also have to connect all edge event points with same distance to split events with same distance
	Point splitPoint = m_events[0].m_point;
	double distance =  m_events[0].m_distanceToLine;
	for ( size_t i=1; i<eventCount(); ++i ) {
		if ( m_events[i].m_isSplit && ( IBK::nearly_equal<3>( m_events[i].m_distanceToLine, distance ) || ( m_events[i].m_point == splitPoint ) ) )
			continue;
		else if ( !( m_events[i].m_point == splitPoint ) )
			addSkeletonLine( IBK::Line ( m_events[i].m_point.toIbkPoint(), splitPoint.toIbkPoint() ) );
	}

	if (m_events[0].m_isSplit) {
		IBK::IBK_Message("SPLIT EVENT\n", IBK::MSG_PROGRESS, "[Polygon::shrink]", IBK::VL_ALL);
		return shrinkSplit();
	} else {
		IBK::IBK_Message("EDGE EVENT\n", IBK::MSG_PROGRESS, "[Polygon::shrink]", IBK::VL_ALL);
		return shrinkEdge();
	}
}

void Polygon::findSkeletonLines()
{
	std::vector<SKELETON::Polygon>	polys, tempPolys;
	std::vector<IBK::Line>			skeletonLines;

	if (!checkSanity<3>())
		return;

	set(false);

	polys.push_back(*this);

	std::cout << "\nSTART\n";

	int counter = 0;

	try {

		while ( counter < 100 && !polys.empty() && !SKELETON::nearZero<4>( polys[0].area() ) ) {

			std::cout << "\nStep:" << ++counter << " ---------------------------\n";

			m_shrinkedPolygons.push_back(std::vector<Point>());

			std::cout << "\nPoints\n";
			for (size_t j=0; j<polys[0].size(); ++j) {
				std::cout << j << "\t" << polys[0].point(j).m_x << "\t" << polys[0].point(j).m_y << std::endl;
				m_shrinkedPolygons.back().push_back(polys[0].point(j));
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
						  << "\t" << (polys[0].origins()[j].m_isSplit ? "Split Event" : "Edge Event")
						<< "\t" << polys[0].origins()[j].m_point.m_x << "\t\t" << polys[0].origins()[j].m_point.m_y << "\t"
						<< "\t" << polys[0].origins()[j].m_vector.m_x << "\t\t" << polys[0].origins()[j].m_vector.m_y << std::endl;

				SKELETON::Polygon::Origin ori = polys[0].origins()[j];

				//				for ( SKELETON::Polygon::Event event : polys[0].events() ) {
				for ( size_t k=0; k< polys[0].events().size(); k++) {

					IBK::Line line ( ori.m_point.toIbkPoint(),
									 ori.m_point.addVector(ori.m_vector, SKELETON::MAX_SCALE).toIbkPoint() );

					// test whether event point lies on bisector line from origin
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

			if ( !polys[0].skeletonLines().empty())
				for (size_t n = 1; n < polys.size(); ++n)
					polys[n].setSkeletonLines( polys[0].skeletonLines() );

			setSkeletonLines( polys[0].skeletonLines() );

			polys.erase( polys.begin() );

			// check for area
			std::vector<size_t> delPolys;
			for ( size_t l=0; l<polys.size(); ++l )
				if ( IBK::nearly_equal<4>( polys[l].area(), 0 ) )
					delPolys.push_back(l);

			for ( size_t l=delPolys.size(); l>0; --l )
				polys.erase( polys.begin()+delPolys[l-1] );

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
}

bool Polygon::skeleton()
{
	return true;
}

size_t Polygon::eventCount() {
	size_t count=0;
	for (size_t i = 1; i < m_events.size(); ++i) {
		if ( IBK::nearly_equal<3>( m_events[i].m_distanceToLine, m_events[i-1].m_distanceToLine ) )
			++count;
		else
			return ++count;
	}
}

std::vector<Polygon> Polygon::shrinkSplit() {
	// we start form the split point we found
	// we go in both directions till we reach the Corner Point that made the split event
	// we get then new polygons,

	if ( !m_events[0].m_isSplit )
		throw IBK::Exception(IBK::FormatString("Event with shortest Distance is not a Split Event."), "[Polygon::shrinkSplit]");


	CLIPPER::Paths pShrinked;
	CLIPPER::Path p;

	for (size_t i=0; i<size(); ++i)
		p << CLIPPER::IntPoint(m_points[i].m_x*MAX_SCALE, m_points[i].m_y*MAX_SCALE);

	CLIPPER::ClipperOffset co (MAX_SCALE*MAX_SCALE, 0.25);
	co.AddPath(p,CLIPPER::jtMiter,CLIPPER::etClosedPolygon);
	co.Execute(pShrinked, -(m_events[0].m_distanceToLine+MIN_SCALE) * MAX_SCALE );

	std::vector<Polygon> polys;
	Polygon poly;
	IBK::Line l;

	for (size_t i=0; i<pShrinked.size(); ++i) {
		polys.push_back(poly);
		// give back polygon from CLIPPER
		for (size_t j=pShrinked[i].size(); j>0; --j)
			polys[i] << Point ((double)pShrinked[i][j-1].X / MAX_SCALE, (double)pShrinked[i][j-1].Y / MAX_SCALE );

		// check whether there are already any origins
		if ( /*pShrinked.size()>1 && */!m_origins.empty() )
			polys[i].m_origins.insert( polys[i].m_origins.begin(), m_origins.begin(), m_origins.end() );

		polys[i].m_skeletonLines.insert( polys[i].m_skeletonLines.begin(), m_skeletonLines.begin(), m_skeletonLines.end() );

		polys[i].set(false);

		// check for points
		for (size_t k=0; k<m_events.size(); ++k) {
			if ( k==0 || ( IBK::nearly_equal<4>( m_events[k].m_distanceToLine, m_events[k-1].m_distanceToLine ) /*||
														 checkPoints<4>(m_events[k].m_point, m_events[k-1].m_point )*/ ) ) {
				for (size_t j=0; j<polys[i].size(); ++j) {
					if ( (  pShrinked.size()>1 && checkPoints<4>(m_events[k].m_point, polys[i].point(j) ) ) /*||
								   ( eventsSize() > k && checkPoints<4>(m_events[k].m_point, m_events[k+1].m_point ) )*/ )
						polys[i].m_origins.push_back( Origin ( m_events[k].m_point, j, polys[i].bisector(j), true ) );
					//					else if ( k>0 && checkPoints<4>(m_events[k].m_point, m_events[k-1].m_point ) ) {
					//						polys[i].m_origins.push_back( Origin ( m_events[k].m_point, j, polys[i].bisector(j), true ) );
					//						break;
					//					}
					else if ( k>0 && ( ( m_events[k-1].m_isSplit && !m_events[k].m_isSplit ) &&
									   IBK::nearly_equal<3>( m_events[k].m_distanceToLine, m_events[k-1].m_distanceToLine ) ) ) {
						if ( checkPoints<3>( m_events[k-1].m_point, polys[i].m_points[j] ))
							polys[i].m_origins.push_back( SKELETON::Polygon::Origin ( m_events[k-1].m_point, j, polys[i].m_bisectors[j], true ) );

					}
				}
			} else
				break;
		}
	}

	return polys;
}

std::vector<Polygon> Polygon::shrinkEdge() {
	// we start form the split point we found
	// we go in both directions till we reach the Corner Point that made the split event
	// we get then new polygons,

	if ( m_events[0].m_isSplit )
		throw IBK::Exception(IBK::FormatString("Event with shortest Distance is not an Edge Event."), "[Polygon::shrinkSplit]");

	if( m_events[0].m_pointsEdge.empty() )
		throw IBK::Exception(IBK::FormatString("No Origin Edge in Events set."), "[Polygon::shrinkSplit]");


	CLIPPER::Paths pShrinked;
	CLIPPER::Path p;

	//	for (size_t i=size(); i>0; --i)
	//		p << CLIPPER::IntPoint(m_points[i-1].m_x*MAX_SCALE, m_points[i-1].m_y*MAX_SCALE);

	for (size_t i=0; i<size(); ++i)
		p << CLIPPER::IntPoint(m_points[i].m_x*MAX_SCALE_CLIPPER, m_points[i].m_y*MAX_SCALE_CLIPPER);


	CLIPPER::ClipperOffset co (MAX_SCALE_CLIPPER*MAX_SCALE_CLIPPER, 0.25);
	co.AddPath(p,CLIPPER::jtMiter,CLIPPER::etClosedPolygon);
	co.Execute(pShrinked, -(m_events[0].m_distanceToLine+MIN_SCALE_CLIPPER) * MAX_SCALE_CLIPPER );

	std::vector<Polygon> polys;
	Polygon poly;
	IBK::Line l;

	if ( !pShrinked.empty() ) {
		for (size_t i=0; i<pShrinked.size(); ++i) {
			polys.push_back(poly);
			for (size_t j=pShrinked[i].size(); j>0; --j)
				polys[i] << Point ((double)pShrinked[i][j-1].X / MAX_SCALE_CLIPPER, (double)pShrinked[i][j-1].Y / MAX_SCALE_CLIPPER );

			//			polys[i].checkSanity<3>();

			if ( !polys[i].checkSanity<5>() )
				continue;

			try {
				polys[i].set(true);
			} catch (IBK::Exception &ex) {
				ex.writeMsgStackToError();
				throw IBK::Exception ( "Could not set Polygon", "[Polygon::shrinkEdge]" );
			}

			// check whether there are already any origins
			if ( m_origins.empty() )
				polys[i].m_origins.push_back( Origin ( m_events[0].m_point, m_events[0].m_pointsEdge[0], m_bisectors[m_events[0].m_pointsEdge[0]] , false) );
			else {
				polys[i].m_origins.insert( polys[i].m_origins.begin(), m_origins.begin(), m_origins.end() );
			}
			for (size_t k=0; k<polys[i].size();++k) {
				if ( checkPoints<3>( m_events[0].m_point, polys[i].point(k) ) )
					polys[i].m_origins.push_back( Origin ( m_events[0].m_point, m_events[0].m_pointsEdge[0], polys[i].bisector(k) , false) );
			}

			polys[i].m_skeletonLines.insert( polys[i].m_skeletonLines.begin(), m_skeletonLines.begin(), m_skeletonLines.end() );

			for (size_t k=0; k<m_origins.size(); ++k) {
				for (size_t j=0; j<polys[i].size(); ++j) {

					if ( nearZero<3>( distancePointToLine( polys[i].point(j).toIbkPoint(),
														   IBK::Line (m_origins[k].m_point.addVector(m_origins[k].m_vector,MAX_SCALE).toIbkPoint(),
																	  m_origins[k].m_point.toIbkPoint()) ) ) )
						polys[i].m_origins.push_back( Origin ( m_origins[k].m_point, j, m_origins[k].m_vector, m_origins[k].m_isSplit ) );
					if ( checkPoints<3>(m_events[0].m_point, polys[i].point(j)) )
						polys[i].m_origins.push_back( Origin ( m_events[0].m_point, j, polys[i].bisector(j), false ) );
				}
			}
		}
		// check for final polygons, we find it by checking if the size is less then 4
		// so that means that we find a triangle.
		// now we check all origins, if we can connect it to our final edge event

		// go through all new polygons
		for (size_t i=0; i<polys.size(); ++i) {
			// go through all origins in new poly
			for (size_t j=0; j<polys[i].origins().size(); ++j) {
				// go through all events of new poly
				for (size_t k=0; k<polys[i].eventsSize(); ++k) {
					// make bisector vector of origin point
					IBK::Line l1 (  polys[i].m_origins[j].m_point.toIbkPoint(),
									polys[i].m_origins[j].m_point.addVector(polys[i].m_origins[j].m_vector, MAX_SCALE).toIbkPoint() );
					// check whether bisector of origin cuts new event point
					if ( ( k == 0 || IBK::nearly_equal<4> ( polys[i].event(k).m_distanceToLine, polys[i].event(k-1).m_distanceToLine ) ) &&
						 nearZero<3> ( distancePointToLine(  polys[i].event(k).m_point.toIbkPoint(), l1) ) ) {
						polys[i].addSkeletonLine( IBK::Line ( polys[i].event(k).m_point.toIbkPoint(),
															  polys[i].m_origins[j].m_point.toIbkPoint() ) );
						//						break;
					}
				}
			}
		}
	} else
		IBK::IBK_Message( IBK::FormatString("CLIPPER Could not shrink Polygon!"), IBK::MSG_WARNING, "[Polygon::shrinkEdge]", IBK::VL_ALL);

	return polys;
}

std::vector< std::vector<Polygon::Point> > Polygon::shrinkedPolygons() const
{
	return m_shrinkedPolygons;
}

Polygon::Event Polygon::event(const size_t &eventIdx) {

	if(m_events.empty())
		throw IBK::Exception(IBK::FormatString("Events are not set in Polygon.").arg(m_bisectors.size()), "[Polygon::split]");

	if(eventIdx > m_events.size())
		throw IBK::Exception(IBK::FormatString("Event Index out of Range. Maximum Size is %1").arg(m_events.size()), "[Polygon::split]");

	return m_events[eventIdx];
}

size_t Polygon::eventsSize() {
	//	if(m_events.empty())
	//		throw IBK::Exception(IBK::FormatString("Events are not set in Polygon.\n").arg(m_bisectors.size()), "[Polygon::events]");

	return m_events.size();
}

std::vector<Polygon::Event> Polygon::events()
{
	return m_events;
}

std::vector<Polygon::Point> Polygon::points()
{
	return m_points;
}

Polygon::Point Polygon::point(const size_t &pointIdx) {
	return m_points[pointIdx];
}

bool Polygon::sortEvents() {
	std::sort(m_events.begin(), m_events.end());
	return true;
}

template<unsigned int digits>
bool Polygon::checkSanity() {
	size_t iN;
	std::vector<size_t> delPoints;
	// check if two or more points have the same coordinates
	for (size_t i=0; i<size(); ++i) {
		iN = modPlus(i, size());
		// first store points that need to be deleted
		if ( SKELETON::checkPoints<3>(m_points[i], m_points[iN]) ) {
			delPoints.push_back(i);
		}
	}
	// delete points
	for (std::vector<size_t>::reverse_iterator i = delPoints.rbegin();
		 i != delPoints.rend(); ++i) {
		int test = *i;
		m_points.erase( m_points.begin() + (int)*i );
	}
	if ( size()<3 )
		return false;
	else
		return true;
}

double Polygon::area()
{
	return m_area;
}

std::vector<Polygon::Origin> Polygon::origins()
{
	return m_origins;
}

std::vector< IBK::Line > Polygon::skeletonLines()
{
	return m_skeletonLines;
}

std::vector<IBK::Line> Polygon::vertexLines()
{
	return m_vertexLines;
}

void Polygon::addSkeletonLine( const IBK::Line &line ) {
	bool addLine = true;
	for (size_t i=0; i<m_skeletonLines.size(); ++i) {
		if ( ( checkPoints<3> ( line.m_p1, m_skeletonLines[i].m_p1 ) &&
			   checkPoints<3> ( line.m_p2, m_skeletonLines[i].m_p2 ) ) ||
			 ( checkPoints<3> ( line.m_p1, m_skeletonLines[i].m_p2 ) &&
			   checkPoints<3> ( line.m_p2, m_skeletonLines[i].m_p1 ) )) {
			addLine = false;
			break;
		}
	}
	if ( addLine )
		m_skeletonLines.push_back(line);
}

void Polygon::addEvent( const Event &event ) {
	bool addEvent = true;
	for (size_t i=0; i<m_events.size(); ++i) {
		if ( m_events[i] == event ) {
			addEvent = false;
			return;
		}
	}
	if ( addEvent )
		m_events.push_back(event);
}

size_t Polygon::skeletons()
{
	return m_skeletonLines.size();
}

IBK::Line Polygon::skeleton(const size_t &lineIdx)
{
	if(m_skeletonLines.empty())
		throw IBK::Exception(IBK::FormatString("Skeleton Lines are not set in Polygon."), "[Polygon::skeletons]");
	if(lineIdx > skeletons()-1 )
		throw IBK::Exception(IBK::FormatString("Skeleton Line Index out of range."), "[Polygon::skeletons]");

	return m_skeletonLines[lineIdx];
}

void Polygon::setSkeletonLines(const std::vector<IBK::Line> &skeletonLines) {

	for ( size_t j=0; j < skeletonLines.size(); ++j )
		addSkeletonLine( skeletonLines[j]);
	return;
}

void Polygon::findVertexLines()
{
	double distance = MAX_SCALE;
	IBK::Line lineTmp;
	for ( size_t i=0; i<size(); ++i ) {
		for ( size_t j=0; j<m_skeletonLines.size(); ++j ) {
			if ( nearZero<3>( distancePointToLine( m_skeletonLines[j].m_p1, IBK::Line ( m_points[i].toIbkPoint(), m_points[i].addVector( m_bisectors[i], MAX_SCALE ).toIbkPoint() ) ) ) ) {
				IBK::Line lineTmp2 ( m_points[i].toIbkPoint(), m_skeletonLines[j].m_p1 );
				if ( lineLength(lineTmp2) < distance ) {
					lineTmp = lineTmp2;
					distance = lineLength(lineTmp);
				}
			}
			else if ( nearZero<3>( distancePointToLine( m_skeletonLines[j].m_p2, IBK::Line ( m_points[i].toIbkPoint(), m_points[i].addVector( m_bisectors[i], MAX_SCALE ).toIbkPoint() ) ) ) ) {
				IBK::Line lineTmp2 ( m_points[i].toIbkPoint(), m_skeletonLines[j].m_p2 );
				if ( lineLength(lineTmp2) < distance ) {
					lineTmp = lineTmp2;
					distance = lineLength(lineTmp);
				}
			}
		}
		m_vertexLines.push_back( lineTmp );
		distance = MAX_SCALE;
	}
}



}
