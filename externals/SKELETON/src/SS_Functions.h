#ifndef SS_FUNCTIONS_H
#define SS_FUNCTIONS_H

#include <IBK_point.h>
#include <IBK_math.h>

#include "SS_Polygon.h"

namespace SKELETON {

/*! Checks wether two Points are nearly eaqual. Means that they have the same coordinates */
template<unsigned int digits>
bool checkPoints ( const SKELETON::Polygon::Point &p, const SKELETON::Polygon::Point &pOther) {
    if ( IBK::nearly_equal<digits>(p.m_x, pOther.m_x) && IBK::nearly_equal<digits>(p.m_y, pOther.m_y) )
        return true;
    else
        return false;
}

/*! Gives back the vector between two Points
    \param normalized Sets wether the Vector needs tp be normalized
    */
static IBK::point2D<double> vector ( const SKELETON::Polygon::Point &p, const SKELETON::Polygon::Point &pOther, bool normalized){
    IBKMK::Vector3D vector (p.m_x-pOther.m_x, p.m_y-pOther.m_y, 0.0);

    if(IBK::nearly_equal<4>(vector.magnitude(),0.0))
        throw IBK::Exception(IBK::FormatString("Vector Length ist equal to Zero!"), "[SKELETON::vector]");

    if(normalized){
        vector.normalize();
    }
    return IBK::point2D<double>( vector.m_x, vector.m_y );
}

static double distancePointToLine ( const IBK::point2D<double> &p, const IBK::Line &l ) {
    IBKMK::Vector3D vl (l.m_p2.m_x-l.m_p1.m_x, l.m_p2.m_y-l.m_p1.m_y, 0.0);
    IBKMK::Vector3D vP (p.m_x-l.m_p1.m_x, p.m_y-l.m_p1.m_y, 0.0);
    // find intersection point between both lines
    double c1	= vl.scalarProduct(vl);
    double c2	= vP.scalarProduct(vl);
    double b	= c1 / c2;
    // determine Point
    IBK::point2D<double> Pb (l.m_p1.m_x+b*vl.m_x, l.m_p1.m_y+b*vl.m_y);
    IBKMK::Vector3D vNormal (p.m_x-Pb.m_x,p.m_y-Pb.m_y,0.0);
    if ( IBK::nearly_equal<4>( vNormal.magnitude(), 0.0 ) )
        throw IBK::Exception(IBK::FormatString("Vector Length ist equal to Zero!"), "[SKELETON::distancePointToLine]");

    return vNormal.magnitude();
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
}


#endif // SS_FUNCTIONS_H
