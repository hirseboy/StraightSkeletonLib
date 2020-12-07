/*	Copyright (c) 2001-2020, Institut für Bauklimatik, TU Dresden, Germany

	Written by S. Hirth
	All rights reserved.

	This file is part of the SKELETON Library.

	Redistribution and use in source and binary forms, with or without modification,
	are permitted provided that the following conditions are met:

	1. Redistributions of source code must retain the above copyright notice, this
	   list of conditions and the following disclaimer.

	2. Redistributions in binary form must reproduce the above copyright notice,
	   this list of conditions and the following disclaimer in the documentation
	   and/or other materials provided with the distribution.

	3. Neither the name of the copyright holder nor the names of its contributors
	   may be used to endorse or promote products derived from this software without
	   specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
	ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
	ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


	This library contains derivative work based on other open-source libraries.
	See OTHER_LICENCES and source code headers for details.

*/

#ifndef SS_POLYGON_H
#define SS_POLYGON_H

#include <IBK_point.h>
#include <IBKMK_Vector3D.h>
#include <IBK_Line.h>
#include <IBK_math.h>

namespace SKELETON {

class Polygon
{
public:
	Polygon(){}

	Polygon(const std::vector< IBK::point2D<double> > &points, bool setEvents = true);

	/*! Destructor */
	~Polygon();

	/*! Contains the data entries in the material table of the geometry section. */
	struct Point {
		/*! Constructor. */
		Point(){}

		Point(const double &x, const double &y) :
			m_x(x),
			m_y(y)
		{}

		Point(const IBK::point2D<double> &point) :
			m_x(point.m_x),
			m_y(point.m_y)
		{}

		Point(const double &x, const double &y, const size_t &pointIdx) :
			m_x(x),
			m_y(y),
			m_pointIdx(pointIdx)
		{}

		Point addVector(const IBKMK::Vector3D &vector, const long long int &factor) {
			return Point (m_x+vector.m_x*factor, m_y+vector.m_y*factor);
		}

		IBK::point2D<double> toIbkPoint() {
			return IBK::point2D<double> (m_x, m_y);
		}

		IBKMK::Vector3D toIbkVector3D() {
			return IBKMK::Vector3D (m_x, m_y, 0.0);
		}

		double				m_x;				///< x value
		double				m_y;				///< y value
		size_t				m_pointIdx = 0;		///< index of origin of edge for shrinking processes
	};

	struct Event {

		Event(){}

		Event(const Point &point, const double &distanceToLine, const std::vector<size_t> &linesSplit,
			  const std::vector<size_t> &pointsEdge, const bool &visited, const bool &isSplit) :
			m_point(point),
			m_linesSplit(linesSplit),
			m_pointsEdge(pointsEdge),
			m_distanceToLine(distanceToLine),
			m_visited(visited),
			m_isSplit(isSplit)
		{}

		Event(const Point &point, const double &distanceToLine, const size_t &lineSplit,
			  const size_t &pointEdge, const bool &visited, const bool &isSplit) :
			m_point(point),
			m_distanceToLine(distanceToLine),
			m_visited(visited),
			m_isSplit(isSplit)
		{
			m_linesSplit.push_back(lineSplit);
			m_pointsEdge.push_back(pointEdge);
		}

		Point					m_point;				///< Stores Point Geometry
		std::vector<size_t>		m_linesSplit;			///< Vector with Indices of Polygon Line Segments refering to Split Event
		std::vector<size_t>		m_pointsEdge;			///< Vector with Indices of Polygon Corner Points refering to Edge Event
		double					m_distanceToLine;		///< Distance to Line Segment
		bool					m_visited;				///< Is Event visited
		bool					m_isSplit;				///< Is it a Split Event

		bool operator<(const Event &other){
			if ( !IBK::nearly_equal<4>( m_distanceToLine, other.m_distanceToLine) )
				return ( m_distanceToLine < other.m_distanceToLine ) ;
			else
				return ( m_isSplit && !(m_isSplit == other.m_isSplit) );
		}
	};

	struct Origin {

		Origin(){}

		Origin(const Point &point, const size_t &pointIdx, const IBKMK::Vector3D &vector, const bool &isSplit):
			m_point(point),
			m_pointIdx(pointIdx),
			m_vector(vector),
			m_isSplit(isSplit)
		{}

		Point                   m_point;                ///< Origin Point
		size_t                  m_pointIdx;             ///< Point Index
		IBKMK::Vector3D         m_vector;               ///< Vector to Split Event
		bool                    m_isSplit;              ///< if true Split Event is Origin
	};

	struct splitPoint {

		splitPoint(){}

		splitPoint(const IBK::Line &line, const IBK::point2D<double> &point, const bool &intersected):
			m_line(line),
			m_intersected(intersected),
			m_splitPoint(point)
		{}

		IBK::Line               m_line;
		bool                    m_intersected;
		IBK::Line               m_bisectorLine;
		bool                    m_bisectorIntersected;
		Point					m_splitPoint;

	};

	/*! Sets Bisectors, Vectors and Lines of Polygon */
	bool set(bool setEvents);

	/*! Sets the Bisector Vectors of the Polygon Corner Points */
	bool setBisectors();

	/*! Sets the Vectors for Point i to Point i+1 */
	bool setVectors();

	/*! Sets the Lines, Line Vectors and its Lenghts of the Polygon */
	bool setLines();

	/*! Sets Edge Events with Distance to Line Segment */
	bool setEdgeEvents();

	/*! Sets Split Events with Distance to Opposite Line Segment with the Triangle Method */
	bool setSplitEventsTrianlge();

	/*! Sets Split Events with Distance to Opposite Line Segment */
	bool setSplitEventsBisector();

	/*! Sets the Area of the Polygon */
	bool setArea();

	/*! */
	void setSkeletonLines(const std::vector<IBK::Line> &skeletonLines);

	/*! Finds all bisector skeleton lines */
	void findVertexLines();

	/*! Checks if the Corner Point of the Polygon is Convex */
	bool convex(const size_t &pointIdx);

	/*! Gives back the intersection point of two adjacent corner bisectors. True if Point is found and in Polygon
		\param lineIdx Is the Line Index of the Line Segment the Intersection Point is wanted
	*/
	bool bisectorIntersection(const size_t &lineIdx, Point &p);

	/*! Checks wheather point lies on a polygon line */
	template <size_t digits>
	bool pointOnLine(const IBK::point2D<double> &point);

	/*! Checks wheather point lies on a polygon point */
	template<size_t digits>
	bool pointOnPoint(const IBK::point2D<double> &point);

	/*! Returns the number of polygon points */
	size_t size() const;

	/*! Returns the bisector vector of a polygon corner with its pointIdx */
	IBKMK::Vector3D bisector(const size_t &pointIdx);

	/*! Returns the distance to specified Line Segmetn of the Polygon */
	double distanceToLine(const size_t &pointIdx);

	/*! Shrinks the Polygon to the Split or Edge Event wh the shortest Distance */
	std::vector<Polygon> shrink();

	//    /*! Shrinks the Polygon to the next Edge Event and sets the Origin */
	//    std::vector<Polygon> shrink(const std::vector<Polygon::Origin> &origins);

	/*! Returns a Vector with the Straight Skeleton Lines */
	bool skeleton();

	/*! Returns Split or Edge Event with Index eventIdx */
	Event event(const size_t &eventIdx);

	/*! Returns Event Size */
	size_t eventsSize();

	/*! Returns Events of Polygon */
	std::vector< Event > events();

	/*! Returns Points of Polygon */
	std::vector< Point > points();

	/*! Returns Event Size */
	Point point(const size_t &pointIdx);

	/*! Sorts the Events by Distance to Line Segment */
	bool sortEvents();

	/*! Sanity check, that two points do not have the same coordinates */
	template<unsigned int digits>
	bool checkSanity();

	/*! Returns Area of the Polygon */
	double area();

	/*! Returns the Origins of the Polygon */
	std::vector<Origin> origins();

	/*! Returns the Skeleton Lines Size of the Polygon */
	size_t skeletons();

	/*! Returns a Skeleton Line of the Polygon with in Line Index */
	IBK::Line skeleton(const size_t &lineIdx);

	inline void operator <<(const Point &p) {m_points.push_back(p);}

	std::vector<IBK::Line> skeletonLines();

	std::vector<IBK::Line> vertexLines();

	void addSkeletonLine(const IBK::Line &line);
private:

	std::vector<Polygon> shrinkSplit();

	std::vector<Polygon> shrinkEdge();

	std::vector<Point>						m_points;				///< points of polygon
	std::vector<IBK::Line>					m_lines;				///< lines of polygon
	std::vector<IBKMK::Vector3D>			m_bisectors;			///< bisectors of polygon
	bool									m_clockwise = true;		///< clockwise polygon, if true
	std::vector<double>						m_lineLengths;			///< stores lengths of all segments, Segment with index 0 is defined from point 0 to 1
	std::vector<IBKMK::Vector3D>        	m_lineVectors;			///< store the vector from Point i to i+1
	bool									m_open = false;			///< stores if polygon is closed
	std::vector<IBK::Line>					m_vertexLines;			///< Vertex Lines connect corner with event point
	std::vector<IBK::Line>					m_skeletonLines;		///< Skeleton Lines
	std::vector< std::vector<Point> >		m_shrinkedPolygons;		///< Shrinked Polygons
	std::vector<Event>						m_events;				///< List of edge events
	std::vector<Origin>                     m_origins;               ///< Origin Point of Polygon for Shrinking
	double                                  m_area;                 ///< Area of Polygon

};

}

#endif // SS_POLYGON_H
