#include "SS_Polygon.h"
#include "SS_Functions.h"

#include <math.h>
#include <IBK_assert.h>
#include <IBK_Line.h>

namespace SKELETON {

Polygon::Polygon(const std::vector<IBK::point2D<double> > &points)
{
    for (size_t i=0; i<points.size(); ++i) {
		m_points.push_back(Point(points[i]));
    }

    // set m_bisectors
    setBisectors();
}

Polygon::~Polygon()
{
    m_points.clear();
    m_bisectors.clear();
    m_lines.clear();
}

bool Polygon::setBisectors()
{
    size_t iN, iB;
    for(size_t i=0; i<size(); ++i)
    {
         }
    return true;
}

bool Polygon::setVectors()
{
    size_t iN;
    for (size_t i=0; i<size(); ++i) {
        iN = (i+1)%size();
        // first store points that need to be deleted
        m_lineVectors.push_back( SKELETON::vector( m_points[i], m_points[iN], true ) );
    }
    return true;
}

bool Polygon::setLines()
{
    return true;
}

bool Polygon::bisectorIntersection(IBK::point2D<double> &point, size_t lineIdx)
{
    return true;
}

bool Polygon::pointOnLine(IBK::point2D<double> &point)
{
    return true;
}

template <size_t digits>
bool Polygon::pointOnPoint(IBK::point2D<double> &point)
{
    bool onPoint = false;
    size_t iN;
    IBK::Line line;
    for (size_t i=0; i<size(); ++i)
    {
        size_t iN = GeometryFunctions().mod((int)i+1, this->size());
        line = IBK::Line( m_points[iN], m_points[i] );
        double distanceToLine = distancePointToPolygonSegment(point, i);
        if(distanceToLine<0.001 &&
                (  ((m_polyPoints[i].m_x >= point.m_x && point.m_x >= m_polyPoints[iNext].m_x) &&
                    (m_polyPoints[i].m_y >= point.m_y && point.m_y >= m_polyPoints[iNext].m_y))  ||
                   ((m_polyPoints[i].m_x <= point.m_x && point.m_x <= m_polyPoints[iNext].m_x) &&
                    (m_polyPoints[i].m_y <= point.m_y && point.m_y <= m_polyPoints[iNext].m_y)) ))   {
            onPoint=!onPoint;
        }
    }
    return onPoint;
}

size_t Polygon::size() const
{
    return m_points.size();
}

IBK::point2D<double> Polygon::bisector(const size_t &pointIdx)
{
    return IBK::point2D<double>(0.0,0.0);
}

double Polygon::distanceToLine(const size_t &pointIdx)
{
    return 0.0;
}

Polygon::Event Polygon::split(size_t splitIdx)
{
    IBK_ASSERT(m_events[splitIdx].m_isSplit)
    return m_events(splitIdx);
}

Polygon::Event Polygon::edge(size_t edgeIdx)
{
    IBK_ASSERT(!m_events[edgeIdx].m_isSplit)
    return m_events[edgeIdx];
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
            iN = (i+1)%size();
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



}
