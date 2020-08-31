#include <string>

#include <IBK_StringUtils.h>
#include <IBK_Path.h>
#include <IBK_math.h>

#include <SS_Polygon.h>
#include <SS_Functions.h>

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

    std::vector<SKELETON::Polygon> polys = poly.shrink();

    size_t i=0;

    do {
        polys[i].set();

        std::vector<SKELETON::Polygon> polysSkel;
        if ( !SKELETON::nearZero<4>( polys[i].area() ) ) {
            polysSkel = polys[i].shrink();
            polys.insert(polys.end(), polysSkel.begin(), polysSkel.end());
        }
        else {
            ++i;
        }



    } while ( !SKELETON::nearZero<4>( polys[i].area() ) );



    for (size_t i=0; i<polys.size(); ++i) {
        std::cout << std::endl;
        for (size_t j=0; j<polys[i].size(); ++j) {
            std::cout << j << "\t" << polys[i].point(j).m_x << "\t" << polys[i].point(j).m_y << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
