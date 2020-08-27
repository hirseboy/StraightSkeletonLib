#include "SS_Polygon.h"
#include "SS_Functions.h"
#include "SS_Constants.h"

#include <math.h>
#include <cmath>

#include <IBK_assert.h>
#include <IBK_Line.h>
#include <IBK_messages.h>


namespace SKELETON {

Polygon::Polygon(const std::vector<IBK::point2D<double> > &points)
{
	for (size_t i=0; i<points.size(); ++i) {
		m_points.push_back(Point(points[i]));
	}

	if (!set())
		throw IBK::Exception(IBK::FormatString("Polygon could not be initialized."), "[Polygon::Polygon]");
}

Polygon::~Polygon()
{
	m_points.clear();
	m_bisectors.clear();
	m_lines.clear();
	m_lineVectors.clear();
}

bool Polygon::set()
{
	if (!setVectors())
		throw IBK::Exception(IBK::FormatString("Vectors could not be initialized."), "[Polygon::set]");
	if (!setBisectors())
		throw IBK::Exception(IBK::FormatString("Bisectors could not be initialized."), "[Polygon::set]");
	if (!setLines())
		throw IBK::Exception(IBK::FormatString("Lines could not be initialized."), "[Polygon::set]");
}

bool Polygon::setBisectors()
{
	m_bisectors.clear();

	size_t iB;

	for(size_t i=0; i<size(); ++i)
	{
		iB = modMinus(i, size());
		IBKMK::Vector3D vBisector = m_lineVectors[i] - m_lineVectors[iB];
		vBisector.normalize();

		m_bisectors.push_back(vBisector);
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
	}
	return true;
}

bool Polygon::setEdgeEvents()
{
	if(m_points.empty())
		throw IBK::Exception(IBK::FormatString("Points of Polygon are not set."), "[Polygon::setEdgeEvents]");

	for (size_t i=0; i<m_points.size(); ++i)
	{
		Point p;
		if ( !bisectorIntersection(i, p) ) {
			IBK::IBK_Message( IBK::FormatString("Did not find an Intersection point for Line Segment with Index %1").arg(i), IBK::MSG_CONTINUED );
			continue;
		}

		double d = distancePointToLine(p.toIbkPoint(), m_lines[i]);
		// if distToLine is NaN set it to 0.0
		d = (d != d) ? 0.0 : d;

		if ( pointInPolygon(p, m_points) ) {
			// check that there is no doubling in Edge Event Points
			bool inList = false;
			for(size_t j=0; j<m_events.size(); ++j)
				if (checkPoints<4>(p, m_events[j].m_point) && IBK::nearly_equal<4>(d,m_events[j].m_distanceToLine) && !m_events[j].m_isSplit) {
					inList = true;
					m_events[j].m_pointsEdge.push_back(i);
				}
			if (!inList)
				m_events.push_back(Event (p, d, std::vector<size_t>(0), std::vector<size_t>(i), false, false));
		}
	}


}

bool Polygon::setSplitEvents()
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
		throw IBK::Exception(IBK::FormatString("Vectors and Points Sizes do not match."), "[Polygon::convex]");

	if ( m_lines.size() != size())
		throw IBK::Exception(IBK::FormatString("Lines and Points Sizes do not match."), "[Polygon::convex]");

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
				IBK::Line l1 ( m_points[i].addVector(m_lineVectors[i],-1*MAX_SCALE).toIbkPoint(), m_points[i].toIbkPoint());
				IBK::Line l2 ( m_points[i].addVector(m_lineVectors[iB],MAX_SCALE).toIbkPoint(), m_points[i].toIbkPoint());

				IBK::Line lS ( m_points[iS].addVector(m_lineVectors[j],MAX_SCALE).toIbkPoint(), m_points[j].addVector(m_lineVectors[j],-1*MAX_SCALE).toIbkPoint());

				double d = distancePointToLine(m_points[i].toIbkPoint(), m_lines[i]);

				if ( l1.intersects(lS,p1) && l2.intersects(lS,p2) ){
					Point point1 (p1);
					Point point2 (p2);
					Point pCenter;

					// still a bit russian unfortunatly
					std::vector< IBK::point2D<double> > points;
					points.push_back(m_points[i].toIbkPoint());
					points.push_back(p1);
					points.push_back(p2);

					if ( triangleCenter(m_points[i],point1,point2,pCenter) ) {
						if ( pointInPolygon(pCenter, m_points)) {

							Polygon triangle (points);
							double dSplit = triangle.area()/( triangle.m_lineLengths[0] + triangle.m_lineLengths[1] + triangle.m_lineLengths[2] );
							// go through events to avoid ambuigity

							bool inList = false;

							for ( size_t k=0; k<m_events.size(); ++k ) {
								if (checkPoints<4>(pCenter, m_events[j].m_point) && IBK::nearly_equal<4>(d,m_events[k].m_distanceToLine) && m_events[k].m_isSplit) {
									inList = true;
									m_events[j].m_pointsEdge.push_back(i);
								}
								if (!inList) {
									m_events.push_back(Event (pCenter, dSplit, std::vector<size_t>(i),std::vector<size_t>(0),false, true));
									splitEvents = true;
								}
							}
						}
					}
				}
			}
		}
	}

	return splitEvents;
}

bool Polygon::convex(const size_t & pointIdx)
{
	if ( m_lineVectors.empty())
		throw IBK::Exception(IBK::FormatString("Vectors of Polygon are not set."), "[Polygon::convex]");

	if ( m_lineVectors.size() != size())
		throw IBK::Exception(IBK::FormatString("Vectors and Points Sizes do not math."), "[Polygon::convex]");

	double aB, aA, aDiff;
	size_t iB;

	iB = modMinus(pointIdx, size());

	aA = std::atan2(m_lineVectors[pointIdx].m_x,m_lineVectors[pointIdx].m_y);
	aA =(aA < 0) ? (aA + 2*PI) : aA;

	aB = std::atan2(m_lineVectors[iB].m_x,m_lineVectors[iB].m_y);
	aB =(aB < 0) ? (aB + 2*PI) : aB;

	aDiff = aA- aB;
	aDiff = (aDiff<0) ? (aDiff + 2*PI) : aDiff;

	if (IBK::nearly_equal<4>(aDiff,2*PI) || IBK::nearly_equal<4>(aDiff,0.0) )
		return false;
	else if ( (aDiff>PI && m_clockwise) || (aDiff<PI && !m_clockwise) )
		return true;
}

bool Polygon::bisectorIntersection(const size_t & lineIdx, Polygon::Point & p)
{
	if(lineIdx > m_points.size())
		throw IBK::Exception(IBK::FormatString("Line Index out of Range. Maximum Size is %1").arg(m_points.size()), "[Polygon::bisectorIntersection]");

	if(m_bisectors.empty())
		throw IBK::Exception(IBK::FormatString("Bisectors are not set in Polygon."), "[Polygon::bisectorIntersection]");

	IBK_ASSERT(m_points.size() == m_bisectors.size())

			size_t iN, i;
	iN = modPlus(lineIdx, size());


	Point p1 = m_points[iN].addVector(m_bisectors[iN], SKELETON::MAX_SCALE);
	Point p2 = m_points[lineIdx].addVector(m_bisectors[lineIdx], SKELETON::MAX_SCALE);

	IBK::Line l1 ( m_points[iN].toIbkPoint(), p1.toIbkPoint() );
	IBK::Line l2 ( m_points[lineIdx].toIbkPoint(), p2.toIbkPoint() );

	IBK::point2D<double> point;
	if (!l1.intersects(l2,point))
		 IBK::IBK_Message(IBK::FormatString("Line 1 does not intersect Line 2"),IBK::MSG_PROGRESS);
	p = Point (point);

	return true;
}

template <size_t digits>
bool Polygon::pointOnPoint(const IBK::point2D<double> &point)
{
	bool onPoint=false;
	for (size_t i=0; i<this->size(); ++i)
	{
		if( IBK::nearly_equal<digits>(  ) ){
			onPoint=!onPoint;
		}
	}
	return onPoint;
}

template <size_t digits>
bool Polygon::pointOnLine(const IBK::point2D<double> &point)
{
	size_t iN;
	IBK::Line line;
	for (size_t i=0; i<size(); ++i)
		if (SKELETON::pointOnLine(point, m_lines[i]))
			return true;
	return false;
}

size_t Polygon::size() const
{
	if(m_points.empty())
		throw IBK::Exception(IBK::FormatString("Points of Polygon are not set."), "[Polygon::size]");


	return (int)m_points.size();
}

IBKMK::Vector3D Polygon::bisector(const size_t &bisectorIdx)
{
	if(bisectorIdx > m_bisectors.size())
		throw IBK::Exception(IBK::FormatString("Bisector Index out of Range. Maximum Size is %1").arg(m_bisectors.size()), "[Polygon::bisector]");

	return m_bisectors[bisectorIdx];
}

double Polygon::distanceToLine(const size_t &pointIdx)
{
	return 0.0;
}

Polygon::Event Polygon::event(const size_t &eventIdx)
{

	if(m_events.empty())
		throw IBK::Exception(IBK::FormatString("Events are not set in Polygon.").arg(m_bisectors.size()), "[Polygon::split]");

	if(eventIdx > m_events.size())
		throw IBK::Exception(IBK::FormatString("Event Index out of Range. Maximum Size is %1").arg(m_events.size()), "[Polygon::split]");

	return m_events[eventIdx];
}

size_t Polygon::events()
{
	if(m_events.empty())
		throw IBK::Exception(IBK::FormatString("Events are not set in Polygon.").arg(m_bisectors.size()), "[Polygon::events]");

	return m_events.size();
}

bool Polygon::sortEvents()
{
	std::sort(m_events.begin(), m_events.end());
	return true;
}

bool Polygon::checkSanity()
{
	size_t iN;
	std::vector<size_t> delPoints;
	// check if two or more points have the same coordinates
	for (size_t i=0; i<size(); ++i) {
		iN = modPlus(i, size());
		// first store points that need to be deleted
		if ( SKELETON::checkPoints<4>(m_points[i], m_points[iN]) ) {
			delPoints.push_back(iN);
		}
	}
	// delete points
	for (std::vector<size_t>::reverse_iterator i = delPoints.rbegin();
		 i != delPoints.rend(); ++i) {
		int test = *i;
		m_points.erase( m_points.begin() + (int)*i );
	}
	return true;
}

double Polygon::area()
{
	if(m_points.empty())
		throw IBK::Exception(IBK::FormatString("Points of Polygon are not set."), "[Polygon::area]");

	double area = 0.0;
	for (size_t i=0; i<size(); ++i)
	{
		size_t iN = modPlus(i,size());
		area += 0.5 * (m_points[i].m_x*m_points[iN].m_y -  m_points[iN].m_y*m_points[i].m_x);
	}
	return area;
}




}
