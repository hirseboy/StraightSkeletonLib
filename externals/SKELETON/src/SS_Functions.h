#ifndef SS_FUNCTIONS_H
#define SS_FUNCTIONS_H

#include <IBK_point.h>
#include <IBK_math.h>
#include <IBK_messages.h>

#include "SS_Polygon.h"
#include "SS_Constants.h"

namespace SKELETON {

/*! Checks wether two Points are nearly eaqual. Means that they have the same coordinates */
template<unsigned int digits>
bool checkPoints ( const Polygon::Point &p, const Polygon::Point &pOther) {
	if ( IBK::nearly_equal<digits>(p.m_x, pOther.m_x) && IBK::nearly_equal<digits>(p.m_y, pOther.m_y) )
		return true;
	else
		return false;
}

/*! Returns the inner Angle between two Vectors of a Polygon in Degree */
static bool angleVectorsDeg ( const IBKMK::Vector3D &v1, const IBKMK::Vector3D &v2) {
	double dot = v1.scalarProduct(v2);    // between [x1, y1, z1] and [x2, y2, z2]
	double angleInDeg = std::acos( dot/sqrt(v1.magnitude() * v2.magnitude() ) ) / DEG_TO_RAD;

	return angleInDeg;
}

/*! Gives back the vector between two Points
	\param normalized Sets wether the Vector needs tp be normalized
	*/
static IBKMK::Vector3D vector ( const Polygon::Point &p, const Polygon::Point &pOther, bool normalized){
	IBKMK::Vector3D vector (p.m_x-pOther.m_x, p.m_y-pOther.m_y, 0.0);

	if(IBK::nearly_equal<4>(vector.magnitude(),0.0))
		throw IBK::Exception(IBK::FormatString("Vector Length ist equal to Zero!"), "[SKELETON::vector]");

	if(normalized){
		vector.normalize();
	}
	return vector;
}

static double lineLength ( const IBK::Line &line ) {
	IBKMK::Vector3D vec ( line.m_p1.m_x - line.m_p2.m_x, line.m_p1.m_y - line.m_p2.m_y, 0.0 );
	return vec.magnitude();
}


static double distancePointToLine ( const IBK::point2D<double> &p, const IBK::Line &l ) {
	IBKMK::Vector3D vL (l.m_p2.m_x-l.m_p1.m_x, l.m_p2.m_y-l.m_p1.m_y, 0.0);
	IBKMK::Vector3D vP (p.m_x-l.m_p1.m_x, p.m_y-l.m_p1.m_y, 0.0);
	// find intersection point between both lines
	double c1	= vP.scalarProduct(vL);
	double c2	= vL.scalarProduct(vL);
	double b	= c1 / c2;
	// determine Point
	IBK::point2D<double> Pb (l.m_p1.m_x+b*vL.m_x, l.m_p1.m_y+b*vL.m_y);
	IBKMK::Vector3D vNormal (p.m_x-Pb.m_x,p.m_y-Pb.m_y,0.0);
	if ( IBK::nearly_equal<4>( vNormal.magnitude(), 0.0 ) ) {
		IBK::IBK_Message(IBK::FormatString("Vector Length ist equal to Zero!"), IBK::MSG_WARNING, "[SKELETON::distancePointToLine]", IBK::VL_ALL);
		return 0.0;
	}
	return vNormal.magnitude();
}

static bool pointInPolygon(const Polygon::Point &point, const std::vector<Polygon::Point> &points) {
	size_t i, j;
	size_t nvert = points.size();
	bool inPolygon = false;

	for(i = 0, j = nvert - 1; i < nvert; j = i++) {
		if( ( (points[i].m_y > point.m_y ) != (points[j].m_y > point.m_y) ) &&
				(point.m_x < (points[j].m_x - points[i].m_x) * (point.m_y - points[i].m_y) / (points[j].m_y - points[i].m_y) + points[i].m_x)
				)
			inPolygon = !inPolygon;
	}

	return inPolygon;
}

template <size_t digits>
static bool pointOnLine ( const IBK::point2D<double> &p, const IBK::Line &l) {

	double distance = distancePointToLine( p, l );

	if ( distance < (1/std::pow(10,digits)) ) {

		double dL = std::sqrt( IBK::f_powN<2>(l.m_p2.m_x-l.m_p1.m_x) + IBK::f_powN<2>(l.m_p2.m_y-l.m_p1.m_y));
		double dP = std::sqrt( IBK::f_powN<2>(p.m_x-l.m_p1.m_x) + IBK::f_powN<2>(p.m_y-l.m_p1.m_y));

		double scale = dP/dL;

		if (0 < scale < 1)
			return true;
	}
	return false;
}

/*! Calculates the Center Point of a Triange */
static bool triangleCenter(Polygon::Point p1, Polygon::Point p2, Polygon::Point p3, Polygon::Point &pCenter) {

	std::vector< IBK::point2D<double> > points;
	points.push_back(p1.toIbkPoint());
	points.push_back(p2.toIbkPoint());
	points.push_back(p3.toIbkPoint());

	Polygon triangle (points, false);

	if ( !triangle.checkSanity<3>() )
		return false;

	return triangle.bisectorIntersection(0, pCenter);
}

static size_t modMinus( size_t a, size_t b ) {
	int ret = static_cast<int>(a-1) % static_cast<int>(b);
	if(ret < 0)
		ret+=b;
	return static_cast<unsigned int>(ret);
}

static size_t modPlus( size_t a, size_t b ) {
	int ret = static_cast<int>(a+1) % static_cast<int>(b);
	if(ret < 0)
		ret+=b;
	return static_cast<unsigned int>(ret);
}

template <size_t digits>
static bool nearZero( double a ) {
	return IBK::nearly_equal<digits>( a , 0.0 );
}

}


#endif // SS_FUNCTIONS_H
