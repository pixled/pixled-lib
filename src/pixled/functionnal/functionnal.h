#ifndef PIXLED_FUNCTIONNAL_H
#define PIXLED_FUNCTIONNAL_H
#include "../api/functionnal.h"
#include "../api/utils.h"
#include "../api/geometry.h"
#include "../pixel.h"
#include "arithmetic.h"
#include "geometry.h"
#include "random.h"

#include <cmath>
#include <unordered_map>

namespace pixled {

	class X : public api::Function<Coordinate> {
		public:
			using Type = api::Function<Coordinate>::Type;

			Coordinate operator()(api::Point c, Time t) const override {
				return c.x;
			}

			X* copy() const override {return new X;}
	};

	class Y : public api::Function<Coordinate> {
		public:
			using Type = api::Function<Coordinate>::Type;

			Coordinate operator()(api::Point c, Time t) const override {
				return c.y;
			}

			Y* copy() const override {return new Y;}
	};

	class T : public api::Function<Time> {
		public:
			using Type = api::Function<Time>::Type;

			Time operator()(api::Point c, Time t) const override {
				return t;
			}

			T* copy() const override {return new T;}
	};

	class hsb : public api::TernaryFunction<pixled::Color, float, float, float, hsb> {
		public:
			using api::TernaryFunction<pixled::Color, float, float, float, hsb>::TernaryFunction;

			pixled::Color operator()(api::Point c, Time t) const override {
				pixled::Color color;
				color.setHsv((*f1)(c, t), (*f2)(c, t), (*f3)(c, t));
				return color;
			}
	};

	class rgb : public api::TernaryFunction<pixled::Color, uint8_t, uint8_t, uint8_t, rgb> {
		public:
			using api::TernaryFunction<pixled::Color, uint8_t, uint8_t, uint8_t, rgb>::TernaryFunction;

			pixled::Color operator()(api::Point c, Time t) const override {
				pixled::Color color;
				color.setRgb((*f1)(c, t), (*f2)(c, t), (*f3)(c, t));
				return color;
			}
	};
}

#endif
