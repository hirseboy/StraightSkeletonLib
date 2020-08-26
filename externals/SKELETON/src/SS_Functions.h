#ifndef SS_FUNCTIONS_H
#define SS_FUNCTIONS_H

#include <IBK_point.h>
#include <IBK_math.h>

#include "SS_Polygon.h"

namespace SKELETON {



/*! Checks wether two Points are nearly eaqual. Means that they have the same coordinates */
template<unsigned int digits>
bool checkPoints(const SKELETON::Polygon::Point &p, const SKELETON::Polygon::Point &pOther) {
    if ( IBK::nearly_equal<digits>(p.m_x, pOther.m_x) && IBK::nearly_equal<digits>(p.m_y, pOther.m_y) )
        return true;
    else
        return false;
}

static IBK::point2D<double> vector(const SKELETON::Polygon::Point &p, const SKELETON::Polygon::Point &pOther, bool normalized){

    IBKMK::Vector3D vector (p.m_x-pOther.m_x, p.m_y-pOther.m_y, 0.0);
    if(!IBK::nearly_equal<4>(vector.magnitude(),0.0) && normalized){
        vector.normalize();
    }
    return IBK::point2D<double>( vector.m_x, vector.m_y );
}

}
#endif // SS_FUNCTIONS_H
