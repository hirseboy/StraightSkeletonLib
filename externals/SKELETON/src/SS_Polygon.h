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

namespace SKELETON {

class Polygon
{
public:
	Polygon();

	Polygon(const std::vector< IBK::point2D<double> > &points);

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

		Point addVector(const IBKMK::Vector3D &vector, const size_t &factor) {
			return Point (m_x+vector.m_x*factor, m_y+vector.m_y*factor);
		}

		IBK::point2D<double> toIbkPoint() {
			return IBK::point2D<double> (m_x, m_y);
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

		Point					m_point;				///> Stores Point Geometry
		std::vector<size_t>		m_linesSplit;			///< Vector with Indices of Polygon Line Segments refering to Split Event
		std::vector<size_t>		m_pointsEdge;			///< Vector with Indices of Polygon Corner Points refering to Edge Event
		double					m_distanceToLine;		///< Distance to Line Segment
		bool					m_visited;				///< Is Event visited
		bool					m_isSplit;				///< Is it a Split Event

		bool operator<(const Event &other){
			if (m_distanceToLine<other.m_distanceToLine)
				return true;
			else return false;
		}
	};

	/*! Sets Bisectors, Vectors and Lines of Polygon */
	bool set();

	/*! Sets the Bisector Vectors of the Polygon Corner Points */
	bool setBisectors();

	/*! Sets the Vectors for Point i to Point i+1 */
	bool setVectors();

	/*! Sets the Lines, Line Vectors and its Lenghts of the Polygon */
	bool setLines();

	/*! Sets Edge Events with Distance to Line Segment */
	bool setEdgeEvents();

	/*! Sets Split Events with Distance to Opposite Line Segment */
	bool setSplitEvents();

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

	/*! Shrinks the polygon to a Bisector Intersection Point in the polygon. Return false, if the point is hitting a
		Split Event, so that it can't be fitted
		\param pointIdx Is the Index of the Corner of the Polygon
	*/
	bool shrinkPolygon(const size_t &pointIdx);

	/*! Returns Split or Edge Event with Index eventIdx */
	Event event(const size_t &eventIdx);

	/*! Returns Event Size */
	size_t events();

	/*! Sorts the Events by Distance to Line Segment */
	bool sortEvents();

	/*! Sanity check, that two points do not have the same coordinates */
	bool checkSanity();

	/*! Returns Area of the Polygon */
	double area();


private:


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

};

}

#endif // SS_POLYGON_H
