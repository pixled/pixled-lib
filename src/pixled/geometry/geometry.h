#ifndef PIXLED_GEOMETRY_GEOMETRY_H
#define PIXLED_GEOMETRY_GEOMETRY_H

#include "../function.h"

namespace pixled { namespace geometry {

	class X : public base::Function<coordinate> {
		public:
			using Type = base::Function<coordinate>::Type;

			coordinate operator()(point c, time t) const override {
				return c.x;
			}

			X* copy() const override {return new X;}
	};

	class Y : public base::Function<coordinate> {
		public:
			using Type = base::Function<coordinate>::Type;

			coordinate operator()(point c, time t) const override {
				return c.y;
			}

			Y* copy() const override {return new Y;}
	};

	class Distance : public Function<Distance, coordinate, point, point> {
		public:
			using Function<Distance, coordinate, point, point>::Function;

			coordinate operator()(point c, time t) const override;
	};
	
	class LineDistance : public Function<LineDistance, coordinate, line, point> {
		public:
			using Function<LineDistance, coordinate, line, point>::Function;

			coordinate operator()(point p, time t) const override;
	};

	class Point : public Function<Point, point, coordinate, coordinate> {
		public:
			using Function<Point, point, coordinate, coordinate>::Function;

			point operator()(point c, time t) const override;
	};

	class AngleDeg : public Function<AngleDeg, angle, float> {
		public:
			using Function<AngleDeg, angle, float>::Function;

			angle operator()(point p, time t) const override;
	};

	class AngleRad : public Function<AngleRad, angle, float> {
		public:
			using Function<AngleRad, angle, float>::Function;

			angle operator()(point p, time t) const override;
	};

	class Line : public Function<Line, line, coordinate, coordinate, coordinate> {
		public:
		using Function<Line, line, coordinate, coordinate, coordinate>::Function;

		line operator()(point p, time t) const override;
	};

	// X = c helper function
	class XLine : public Function<XLine, line, coordinate> {
		public:
		using Function<XLine, line, coordinate>::Function;

		line operator()(point p, time t) const override;
	};

	// Y = c helper function
	class YLine : public Function<YLine, line, coordinate> {
		public:
		using Function<YLine, line, coordinate>::Function;

		line operator()(point p, time t) const override;
	};

	class AlphaLine : public Function<AlphaLine, line, point, angle> {
		public:
			using Function<AlphaLine, line, point, angle>::Function;

			line operator()(point p, time t) const override;
	};

	class PointLine : public Function<PointLine, line, point, point> {
		public:
			using Function<PointLine, line, point, point>::Function;

			line operator()(point p, time t) const override;
	};

	template<typename T>
		class Sin : public Function<Sin<T>, T, T> {
			public:
				using Function<Sin, T, T>::Function;

				T operator()(point c, time t) const override {
					return std::sin(this->template call<0>(c, t));
				}
		};
}}
#endif
