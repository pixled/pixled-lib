#ifndef PIXLED_FUNCTIONNAL_GEOMETRY_H
#define PIXLED_FUNCTIONNAL_GEOMETRY_H

#include "../api/functionnal.h"

namespace pixled {
	class Distance : public api::BinaryFunction<float, api::Point, api::Point, Distance> {
		public:
			using api::BinaryFunction<float, api::Point, api::Point, Distance>::BinaryFunction;

			float operator()(api::Point c, Time t) const override {
				api::Point c1 = (*this->f1)(c, t);
				api::Point c2 = (*this->f2)(c, t);
				return std::sqrt(std::pow(c2.y - c1.y, 2) + std::pow(c2.x - c1.x, 2));
			};
	};
	
	class LineDistance : public api::BinaryFunction<float, api::Line, api::Point, LineDistance> {
		public:
			using api::BinaryFunction<float, api::Line, api::Point, LineDistance>::BinaryFunction;

			float operator()(api::Point p, Time t) const override {
				api::Line line = (*this->f1)(p, t);
				api::Point point = (*this->f2)(p, t);
				return std::abs(line.a * point.x + line.b * point.y + line.c) /
					std::sqrt(std::pow(line.a, 2) + std::pow(line.b, 2));
			}
	};

	class Point : public api::BinaryFunction<api::Point, Coordinate, Coordinate, Point> {
		public:
			using api::BinaryFunction<api::Point, Coordinate, Coordinate, Point>::BinaryFunction;

			api::Point operator()(api::Point c, Time t) const override {
				return {(*this->f1)(c, t), (*this->f2)(c, t)};
			}
	};

	class Line : public api::TernaryFunction<api::Line, float, float, float, Line> {
		public:
		using api::TernaryFunction<api::Line, float, float, float, Line>::TernaryFunction;

		api::Line operator()(api::Point p, Time t) const override {
			return {(*this->f1)(p, t), (*this->f2)(p, t), (*this->f3)(p, t)};
		}
	};

	// X = c helper function
	class XLine : public api::UnaryFunction<api::Line, float, XLine> {
		public:
		using api::UnaryFunction<api::Line, float, XLine>::UnaryFunction;

		api::Line operator()(api::Point p, Time t) const override {
			return {1, 0, -(*this->f)(p, t)};
		}
	};

	// Y = c helper function
	class YLine : public api::UnaryFunction<api::Line, float, YLine> {
		public:
		using api::UnaryFunction<api::Line, float, YLine>::UnaryFunction;

		api::Line operator()(api::Point p, Time t) const override {
			return {0, 1, -(*this->f)(p, t)};
		}
	};

	template<typename T>
		class Sin : public api::UnaryFunction<T, T, Sin<T>> {
			public:
				using api::UnaryFunction<T, T, Sin>::UnaryFunction;

				T operator()(api::Point c, Time t) const override {
					return std::sin((*this->f)(c, t));
				}
		};
}
#endif
