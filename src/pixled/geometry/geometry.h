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

	class Distance : public Function<Distance, float, point, point> {
		public:
			using Function<Distance, float, point, point>::Function;

			float operator()(point c, time t) const override;
	};
	
	class LineDistance : public Function<LineDistance, float, line, point> {
		public:
			using Function<LineDistance, float, line, point>::Function;

			float operator()(point p, time t) const override;
	};

	class Point : public Function<Point, point, coordinate, coordinate> {
		public:
			using Function<Point, point, coordinate, coordinate>::Function;

			point operator()(point c, time t) const override;
	};

	class Line : public Function<Line, line, float, float, float> {
		public:
		using Function<Line, line, float, float, float>::Function;

		line operator()(point p, time t) const override;
	};

	// X = c helper function
	class XLine : public Function<XLine, line, float> {
		public:
		using Function<XLine, line, float>::Function;

		line operator()(point p, time t) const override;
	};

	// Y = c helper function
	class YLine : public Function<YLine, line, float> {
		public:
		using Function<YLine, line, float>::Function;

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
