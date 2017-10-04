// Copyright (C) Geom Software e.U, Bernhard Kornberger, Graz/Austria
//
// This file is part of the Fade2D library. The student license is free
// of charge and covers personal non-commercial research. Licensees
// holding a commercial license may use this file in accordance with
// the Commercial License Agreement.
//
// This software is provided AS IS with NO WARRANTY OF ANY KIND,
// INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE.
//
// Please contact the author if any conditions of this licensing are
// not clear to you.
//
// Author: Bernhard Kornberger, bkorn (at) geom.at
// http://www.geom.at


#pragma once
#include "Point2.h"
#include "common.h"
#if GEOM_PSEUDO3D==GEOM_TRUE
	namespace GEOM_FADE25D {
#elif GEOM_PSEUDO3D==GEOM_FALSE
	namespace GEOM_FADE2D {
#else
	#error GEOM_PSEUDO3D is not defined
#endif

class  GeomTest; // FWD


/** \brief Bbox2 is an axis aligned bounding box.
*
*/
class CLASS_DECLSPEC Bbox2
{
public:
/** \brief Constructor
 *
 * Bounds not initialized
*/
	explicit Bbox2(GeomTest* pGeomTest_=NULL):
		minX(DBL_MAX),minY(DBL_MAX),
		maxX(DBL_MIN),maxY(DBL_MIN),
		bValid(false),pGeomTest(pGeomTest_)
	{
	}

/** \brief Constructor
 *
 * Bounds initialized to the minimal bounding box of the iterator range of points
*/

	Bbox2(	std::vector<Point2>::const_iterator start_it,
			std::vector<Point2>::const_iterator end_it,
			GeomTest* pGeomTest_=NULL)
			:
			minX(DBL_MAX),minY(DBL_MAX),
			maxX(DBL_MIN),maxY(DBL_MIN),
			pGeomTest(pGeomTest_)
	{
		add(start_it,end_it);
	}

/** \brief Are the bounds valid?
 *
 * The bounds are valid when at least one point has been added
*/

	bool isValid() const
	{
		return minX<DBL_MAX;
	}

/** \brief Get corners
 *
 * Convenience function: Returns the 4 corners of the bounding box
 */
	void getCorners(std::vector<Point2>& vBoxCorners) const;


/** \brief Add points
 *
 * Extends the bounding box if required.
* \return true if the bounding box changes, false otherwise
*/

	bool add(std::vector<Point2>::const_iterator start_it,std::vector<Point2>::const_iterator end_it)
	{
		if(start_it==end_it) return false;
		if(bValid)
		{
			double oldMinX(minX),oldMinY(minY),oldMaxX(maxX),oldMaxY(maxY);
			for(;start_it!=end_it;++start_it) treatPointForValidBox(*start_it);
			if(oldMinX!=minX || oldMinY!=minY || oldMaxX!=maxX || oldMaxY!=maxY ) return true;
			return false;
		}
		else
		{
			treatPointForInvalidBox(*start_it);
			++start_it;
			for(;start_it!=end_it;++start_it) treatPointForValidBox(*start_it);
			return true;
		}
	}

/** \brief Add points
 *
 * Extends the bounding box if required.
* \return true if the bounding box changes, false otherwise
*/

	bool add(size_t numPoints,double * coordinates)
	{
#if GEOM_PSEUDO3D==GEOM_TRUE
		const int NUMCOMPONENTS(3);
#else
		const int NUMCOMPONENTS(2);
#endif

		if(numPoints==0) return false;
		double oldMinX(minX),oldMinY(minY),oldMaxX(maxX),oldMaxY(maxY);
		double x(coordinates[0]);
		double y(coordinates[1]);
		if(x<minX) minX=x;
		if(x>maxX) maxX=x;
		if(y<minY) minY=y;
		if(y>maxY) maxY=y;

		for(size_t i=0;i<numPoints;++i)
		{
			double x(coordinates[NUMCOMPONENTS*i]);
			double y(coordinates[NUMCOMPONENTS*i+1]);
			if(x<minX) minX=x;
				else if(x>maxX) maxX=x;
			if(y<minY) minY=y;
				else if(y>maxY) maxY=y;
		}
		bValid=true;
		if(oldMinX!=minX || oldMinY!=minY || oldMaxX!=maxX || oldMaxY!=maxY ) return true;
			else return false;
	}

/** \brief Add a point
 *
 * Extends the bounding box if required.
* \return true if the bounding box changes, false otherwise
*/

	bool add(const Point2& p)
	{
		//std::cout<<"Add point: "<<p<<std::endl;
		if(bValid)
		{
			double oldMinX(minX),oldMinY(minY),oldMaxX(maxX),oldMaxY(maxY);
			treatPointForValidBox(p);
			if(oldMinX!=minX || oldMinY!=minY || oldMaxX!=maxX || oldMaxY!=maxY ) return true;
				else return false;
		}
		else
		{
			treatPointForInvalidBox(p);
			return true;
		}
	}

/** \brief Add a bounding box
 *
 * Extends the bounding box if required.
* \return the resulting bounding box
*/
	Bbox2 operator+(const Bbox2& b)
	{
		if(b.minX<minX) minX=b.minX;
		if(b.maxX>maxX) maxX=b.maxX;
		if(b.minY<minY) minY=b.minY;
		if(b.maxY>maxY) maxY=b.maxY;
		return *this;
	}


#if GEOM_PSEUDO3D==GEOM_TRUE
/** \brief Get the min point
 *
* \return the corner point with the minimum coordinates, the z-coordinate is set to 0
*/
#else
/** \brief Get the min point
 *
* \return the corner point with the minimum coordinates
*/
#endif

	Point2 getMinPoint() const
	{
#if GEOM_PSEUDO3D==GEOM_TRUE
		return Point2(minX,minY,0);
#else
		return Point2(minX,minY);
#endif
	}


#if GEOM_PSEUDO3D==GEOM_TRUE
/** \brief Get the max point
 *
* \return the corner point with the maximum coordinates, the z-coordinate is set to 0
*/
#else
/** \brief Get the max point
 *
* \return the corner point with the maximum coordinates
*/
#endif

	Point2 getMaxPoint() const
	{
#if GEOM_PSEUDO3D==GEOM_TRUE
		return Point2(maxX,maxY,0);
#else
		return Point2(maxX,maxY);
#endif
	}

/** \brief Get minimum coordinate
*
* \return the smallest coordinate value, i.e. min(minX,minY)
*/

	double getMinCoord() const
	{
		if(minX<minY) return minX;
			else return minY;
	}
/** \brief Get maximum coordinate
 *
* \return the largest coordinate value, i.e. max(maxX,maxY)
*/

	double getMaxCoord() const
	{
		if(maxX>maxY) return maxX;
			else return maxY;
	}

/** \brief Get x-range
 *
* \return maxX-minX
*/

	double getRangeX() const
	{
		return maxX-minX;
	}
/** \brief Get y-range
 *
* \return maxY-minY
*/
	double getRangeY() const
	{
		return maxY-minY;
	}

/** \brief Get max range
*
* \return the largest range, i.e. max(getRangeX(),getRangeY())
*/

	double getMaxRange() const
	{
		double range0=getRangeX();
		double range1=getRangeY();
		if(range0>range1) return range0;
		return range1;
	}

/** \brief Get minX
 *
* \return minX
*/
	double get_minX() {return minX;}
/** \brief Get minY
 *
* \return minY
*/
	double get_minY() {return minY;}
/** \brief Get maxX
 *
* \return maxX
*/
	double get_maxX() {return maxX;}
/** \brief Get maxY
 *
* \return maxY
*/
	double get_maxY() {return maxY;}

/** \brief Double the box
 *
* Changes the bounds such that the box grows in each direction by half
* the previous range
*/

	void doubleTheBox();

protected:
	inline void treatPointForValidBox(const Point2& p)
	{
		double x,y;
		p.xy(x,y);
		if(x<minX) minX=x;
			else if(x>maxX) maxX=x;
		if(y<minY) minY=y;
			else if(y>maxY) maxY=y;
	}
	inline void treatPointForInvalidBox(const Point2& p)
	{
		p.xy(minX,minY);
		p.xy(maxX,maxY);
		bValid=true;
	}

protected:
	double minX,minY;
	double maxX,maxY;
	bool bValid;
	friend std::ostream &operator<<(std::ostream &stream, Bbox2& pC);
	GeomTest* pGeomTest;
};


inline std::ostream &operator<<(std::ostream &stream, Bbox2& pC)
{
	stream<<"Bbox2: ("<<pC.minX<<","<<pC.minY<<") -> ("<<pC.maxX<<","<<pC.maxY<<"), rangeX="<<pC.getRangeX()<<", rangeY="<<pC.getRangeY();
	return stream;
}



} // (namespace)
