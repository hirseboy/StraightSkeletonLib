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

    std::vector<SKELETON::Polygon> polys, tempPolys;

    polys.push_back(poly);

    while ( !polys.empty() && !SKELETON::nearZero<4>( polys[0].area() ) ) {

        if ( polys[0].size()>3 ) {
            tempPolys = polys[0].shrink();
            polys.insert( polys.end(), tempPolys.begin(), tempPolys.end() );
        }
        else {
            // insert empty polygon to store last Edge Point
            SKELETON::Polygon tempPoly;
            tempPoly.origins().push_back(SKELETON::Polygon::Origin ( polys[0].event(0).m_point, 0, IBKMK::Vector3D (), false ) );
            polys.insert( polys.end(), tempPoly );
        }

        std::cout << std::endl;
        std::cout << std::endl;
        for (size_t j=0; j<polys[0].size(); ++j) {
            std::cout << j << "\t" << polys[0].point(j).m_x << "\t" << polys[0].point(j).m_y << std::endl;
        }

        for (size_t j=0; j<polys[0].origins().size(); ++j) {
            std::cout << j << "\t" << (polys[0].origins()[j].m_isSplit ? "Split Event" : "Edge Event") << "\t" << polys[0].origins()[j].m_point.m_x << "\t" << polys[0].origins()[j].m_point.m_y << std::endl;
        }

        for (size_t j=0; j<polys[0].skeletons(); ++j) {
            std::cout << j << "\t\t"    << polys[0].skeleton(j).m_p1.m_x << "\t" << polys[0].skeleton(j).m_p1.m_y << "\t\n\t\t"
                                        << polys[0].skeleton(j).m_p2.m_x << "\t" << polys[0].skeleton(j).m_p2.m_y << "\t" << std::endl;
        }

        polys.erase( polys.begin() );
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

    return EXIT_SUCCESS;
}
