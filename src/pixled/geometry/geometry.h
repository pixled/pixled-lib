#ifndef PIXLED_GEOMETRY_GEOMETRY_H
#define PIXLED_GEOMETRY_GEOMETRY_H

#include "../function.h"

namespace pixled { namespace geometry {

	class X : public base::Function<Coordinate> {
		public:
			using Type = base::Function<Coordinate>::Type;

			Coordinate operator()(Point c, Time t) const override {
				return c.x;
			}

			X* copy() const override {return new X;}
	};

	class Y : public base::Function<Coordinate> {
		public:
			using Type = base::Function<Coordinate>::Type;

			Coordinate operator()(Point c, Time t) const override {
				return c.y;
			}

			Y* copy() const override {return new Y;}
	};

	class Distance : public Function<Distance, float, Point, Point> {
		public:
			using Function<Distance, float, Point, Point>::Function;

			float operator()(pixled::Point c, Time t) const override;
	};
	
	class LineDistance : public Function<LineDistance, float, Line, Point> {
		public:
			using Function<LineDistance, float, Line, Point>::Function;

			float operator()(pixled::Point p, Time t) const override;
	};

	class Point : public Function<Point, pixled::Point, Coordinate, Coordinate> {
		public:
			using Function<Point, pixled::Point, Coordinate, Coordinate>::Function;

			pixled::Point operator()(pixled::Point c, Time t) const override;
	};

	class Line : public Function<Line, pixled::Line, float, float, float> {
		public:
		using Function<Line, pixled::Line, float, float, float>::Function;

		pixled::Line operator()(pixled::Point p, Time t) const override;
	};

	// X = c helper function
	class XLine : public Function<XLine, pixled::Line, float> {
		public:
		using Function<XLine, pixled::Line, float>::Function;

		pixled::Line operator()(pixled::Point p, Time t) const override;
	};

	// Y = c helper function
	class YLine : public Function<YLine, pixled::Line, float> {
		public:
		using Function<YLine, pixled::Line, float>::Function;

		pixled::Line operator()(pixled::Point p, Time t) const override;
	};

	template<typename T>
		class Sin : public Function<Sin<T>, T, T> {
			public:
				using Function<Sin, T, T>::Function;

				T operator()(pixled::Point c, Time t) const override {
					return std::sin(this->template call<0>(c, t));
				}
		};
}}
#endif
