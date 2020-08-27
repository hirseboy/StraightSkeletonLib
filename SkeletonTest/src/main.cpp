#include <string>

#include <IBK_StringUtils.h>
#include <IBK_Path.h>
#include <SS_Polygon.h>

int main(int argc, char * argv[])
{
	std::vector< IBK::point2D<double> > points;
	IBK::point2D<double> point;

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

	SKELETON::Polygon poly(points);

	size_t test = poly.size();
	poly.checkSanity();

	poly.setEdgeEvents();
	poly.setSplitEvents();

	for (size_t i=0; i<poly.events(); ++i) {
		std::cout << poly.event(i).m_isSplit << "\t" << poly.event(i).m_point.m_x << "\t" << poly.event(i).m_point.m_y << std::endl;
	}

	return EXIT_SUCCESS;
}
