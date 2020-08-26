#include <string>

#include <IBK_StringUtils.h>
#include <IBK_Path.h>
#include <SS_Polygon.h>

int main(int argc, char * argv[])
{
    std::vector< IBK::point2D<double> > points;
    IBK::point2D<double> point;
    point.set(0,0);
    points.push_back(point);

    point.set(1,0);
    points.push_back(point);

    point.set(2,0);
    points.push_back(point);

    point.set(2,0);
    points.push_back(point);

    point.set(2,0);
    points.push_back(point);

    SKELETON::Polygon poly(points);

    size_t test = poly.size();
    poly.checkSanity();


}
