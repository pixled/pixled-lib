#ifndef PIXLED_GEOMETRY_GEOMETRY_H
#define PIXLED_GEOMETRY_GEOMETRY_H

#include "../function.h"

namespace pixled { namespace geometry {

	/**
	 * X coordinate of the point on which the \Function is currently evaluated.
	 *
	 * @retval coordinate current x coordinate
	 */
	class X : public base::Function<coordinate> {
		public:
			coordinate operator()(led l, time t) const override {
				return l.location.x;
			}

			X* copy() const override {return new X;}
	};

	/**
	 * Y coordinate of the point on which the \Function is currently evaluated.
	 *
	 * @retval coordinate current y coordinate
	 */
	class Y : public base::Function<coordinate> {
		public:
			coordinate operator()(led l, time t) const override {
				return l.location.y;
			}

			Y* copy() const override {return new Y;}
	};

	/**
	 * Index of the led on which the \Function is currently evaluated.
	 *
	 * @retval current led index
	 */
	class I : public base::Function<index_t> {
		public:
			index_t operator()(led l, time t) const override {
				return l.index;
			}

			I* copy() const override {return new I;}
	};

	/**
	 * Computes the euclidian distance between two points.
	 *
	 * @param point p1
	 * @param point p2
	 * @retval coordinate distance between `p1` and `p2`
	 */
	class Distance : public Function<Distance, coordinate, point, point> {
		public:
			using Function<Distance, coordinate, point, point>::Function;

			coordinate operator()(led l, time t) const override;
	};

	/**
	 * Computes the euclidian distance between a point and a line.
	 *
	 * @param line l
	 * @param point p
	 * @retval coordinate distance between `l` and `p`
	 */
	class LineDistance : public Function<LineDistance, coordinate, line, point> {
		public:
			using Function<LineDistance, coordinate, line, point>::Function;

			coordinate operator()(led l, time t) const override;
	};

	/**
	 * Functionnal point definition.
	 *
	 * Notice the difference with pixled::point, that is a **fundamental
	 * type**, returned by this Point \Function.
	 *
	 * Contrary to pixled::point, a Point is defined from two dynamic
	 * \Functions that return X/Y coordinates.
	 *
	 * @param coordinate X coordinate
	 * @param coordinate Y coordinate
	 * @retval point the pixled::point defined by X/Y
	 */
	class Point : public Function<Point, point, coordinate, coordinate> {
		public:
			using Function<Point, point, coordinate, coordinate>::Function;

			point operator()(led l, time t) const override;
	};

	/**
	 * Functionnal angle definition, in degree.
	 *
	 * Notice the difference with pixled::angle, that is a **fundamental
	 * type**, returned by this AngleDeg \Function.
	 *
	 * Contrary to pixled::angle, AngleDeg is defined from a dynamic
	 * \Function that return a value in degree.
	 *
	 * @param float angle value in degree
	 * @retval angle the pixled::angle defined by the specified value
	 */
	class AngleDeg : public Function<AngleDeg, angle, float> {
		public:
			using Function<AngleDeg, angle, float>::Function;

			angle operator()(led l, time t) const override;
	};

	/**
	 * Functionnal angle definition, in radian.
	 *
	 * Notice the difference with pixled::angle, that is a **fundamental
	 * type**, returned by this AngleRad \Function.
	 *
	 * Contrary to pixled::angle, AngleRad is defined from a dynamic
	 * \Function that return a value in radian.
	 *
	 * @param float angle value in radian
	 * @retval angle the pixled::angle defined by the specified value
	 */
	class AngleRad : public Function<AngleRad, angle, float> {
		public:
			using Function<AngleRad, angle, float>::Function;

			angle operator()(led l, time t) const override;
	};

	/**
	 * Functionnal line definition.
	 *
	 * Notice the difference with pixled::line, that is a **fundamental
	 * type**, returned by this Line \Function.
	 *
	 * Contrary to pixled::line, a Line is defined from dynamic
	 * \Functions that return the pixled::line parameters.
	 *
	 * @param coordinate a
	 * @param coordinate b
	 * @param coordinate c
	 * @retval line line defined by `a*x + b*y + c=0`
	 */
	class Line : public Function<Line, line, coordinate, coordinate, coordinate> {
		public:
		using Function<Line, line, coordinate, coordinate, coordinate>::Function;

		line operator()(led l, time t) const override;
	};

	/**
	 * Defines a vertial line.
	 *
	 * @param coordinate c
	 * @retval line line defined by `x=c`
	 */
	class XLine : public Function<XLine, line, coordinate> {
		public:
		using Function<XLine, line, coordinate>::Function;

		line operator()(led l, time t) const override;
	};

	/**
	 * Defines an horizontal line.
	 *
	 * @param coordinate c
	 * @retval line line defined by `y=c`
	 */
	class YLine : public Function<YLine, line, coordinate> {
		public:
		using Function<YLine, line, coordinate>::Function;

		line operator()(led l, time t) const override;
	};

	/**
	 * Defines a line from a point and an angle.
	 *
	 * @param point p
	 * @param angle a
	 * @retval line passing through p, forming an angle a with the horizontal
	 */
	class AlphaLine : public Function<AlphaLine, line, point, angle> {
		public:
			using Function<AlphaLine, line, point, angle>::Function;

			line operator()(led l, time t) const override;
	};

	/**
	 * Defines a line from two points.
	 *
	 * @param point p1
	 * @param point p2
	 * @retval line passing through p1 and p2
	 */
	class PointLine : public Function<PointLine, line, point, point> {
		public:
			using Function<PointLine, line, point, point>::Function;

			line operator()(led l, time t) const override;
	};
}}
#endif
