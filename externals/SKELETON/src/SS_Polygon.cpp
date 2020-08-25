#include "SS_Polygon.h"

namespace SKELETON {

Polygon::Polygon(const std::vector<IBK::point2D<double> > &points)
{
	m_points.clear();
	for (size_t i=0; i<points.size(); ++i) {
		m_points.push_back(Point(points[i]));
	}
}



}
