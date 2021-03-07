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

	class Distance : public VarFunction<Distance, float, Point, Point> {
		public:
			using VarFunction<Distance, float, Point, Point>::VarFunction;

			float operator()(pixled::Point c, Time t) const override;
	};
	
	class LineDistance : public VarFunction<LineDistance, float, Line, Point> {
		public:
			using VarFunction<LineDistance, float, Line, Point>::VarFunction;

			float operator()(pixled::Point p, Time t) const override;
	};

	class Point : public VarFunction<Point, pixled::Point, Coordinate, Coordinate> {
		public:
			using VarFunction<Point, pixled::Point, Coordinate, Coordinate>::VarFunction;

			pixled::Point operator()(pixled::Point c, Time t) const override;
	};

	class Line : public VarFunction<Line, pixled::Line, float, float, float> {
		public:
		using VarFunction<Line, pixled::Line, float, float, float>::VarFunction;

		pixled::Line operator()(pixled::Point p, Time t) const override;
	};

	// X = c helper function
	class XLine : public VarFunction<XLine, pixled::Line, float> {
		public:
		using VarFunction<XLine, pixled::Line, float>::VarFunction;

		pixled::Line operator()(pixled::Point p, Time t) const override;
	};

	// Y = c helper function
	class YLine : public VarFunction<YLine, pixled::Line, float> {
		public:
		using VarFunction<YLine, pixled::Line, float>::VarFunction;

		pixled::Line operator()(pixled::Point p, Time t) const override;
	};

	template<typename T>
		class Sin : public VarFunction<Sin<T>, T, T> {
			public:
				using VarFunction<Sin, T, T>::VarFunction;

				T operator()(pixled::Point c, Time t) const override {
					return std::sin(this->template call<0>(c, t));
				}
		};
}}
#endif
