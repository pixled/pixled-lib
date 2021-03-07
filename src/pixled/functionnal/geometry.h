#ifndef PIXLED_FUNCTIONNAL_GEOMETRY_H
#define PIXLED_FUNCTIONNAL_GEOMETRY_H

#include "../api/functionnal.h"

namespace pixled { namespace geometry {
	class Distance : public VarFunction<Distance, float, Point, Point> {
		public:
			using VarFunction<Distance, float, Point, Point>::VarFunction;

			float operator()(pixled::Point c, Time t) const override {
				Point c1 = this->call<0>(c, t);
				Point c2 = this->call<1>(c, t);
				return std::sqrt(std::pow(c2.y - c1.y, 2) + std::pow(c2.x - c1.x, 2));
			};
	};
	
	class LineDistance : public VarFunction<LineDistance, float, Line, Point> {
		public:
			using VarFunction<LineDistance, float, Line, Point>::VarFunction;

			float operator()(pixled::Point p, Time t) const override {
				Line line = this->call<0>(p, t);
				Point point = this->call<1>(p, t);
				return std::abs(line.a * point.x + line.b * point.y + line.c) /
					std::sqrt(std::pow(line.a, 2) + std::pow(line.b, 2));
			}
	};

	class Point : public VarFunction<pixled::Point, pixled::Point, Coordinate, Coordinate> {
		public:
			using VarFunction<pixled::Point, pixled::Point, Coordinate, Coordinate>::VarFunction;

			pixled::Point operator()(pixled::Point c, Time t) const override {
				return {this->call<0>(c, t), this->call<1>(c, t)};
			}
	};

	class Line : public VarFunction<Line, Line, float, float, float> {
		public:
		using VarFunction<Line, Line, float, float, float>::VarFunction;

		Line operator()(pixled::Point p, Time t) const override {
			return {this->call<0>(p, t), this->call<1>(p, t), this->call<2>(p, t)};
		}
	};

	// X = c helper function
	class XLine : public VarFunction<XLine, Line, float> {
		public:
		using VarFunction<XLine, Line, float>::VarFunction;

		Line operator()(pixled::Point p, Time t) const override {
			return {1, 0, -this->call<0>(p, t)};
		}
	};

	// Y = c helper function
	class YLine : public VarFunction<YLine, Line, float> {
		public:
		using VarFunction<YLine, Line, float>::VarFunction;

		Line operator()(pixled::Point p, Time t) const override {
			return {0, 1, -this->call<0>(p, t)};
		}
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
