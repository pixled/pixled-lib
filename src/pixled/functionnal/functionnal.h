#ifndef PIXLED_FUNCTIONNAL_H
#define PIXLED_FUNCTIONNAL_H
#include "../api/functionnal.h"
#include "../api/utils.h"
#include "../api/geometry.h"
#include "../pixel.h"
#include "arithmetic.h"
#include "geometry.h"
#include "random.h"
#include "signals.h"

#include <cmath>
#include <unordered_map>

namespace pixled {

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

	class T : public base::Function<Time> {
		public:
			using Type = base::Function<Time>::Type;

			Time operator()(Point c, Time t) const override {
				return t;
			}

			T* copy() const override {return new T;}
	};

	class hsb : public VarFunction<hsb, pixled::Color, float, float, float> {
		public:
			using VarFunction<hsb, pixled::Color, float, float, float>::VarFunction;

			pixled::Color operator()(Point c, Time t) const override {
				pixled::Color color;
				color.setHsb(this->call<0>(c, t), this->call<1>(c, t), this->call<2>(c, t));
				return color;
			}
	};

	class rgb : public VarFunction<rgb, pixled::Color, uint8_t, uint8_t, uint8_t> {
		public:
			using VarFunction<rgb, pixled::Color, uint8_t, uint8_t, uint8_t>::VarFunction;

			pixled::Color operator()(Point c, Time t) const override {
				pixled::Color color;
				color.setRgb(this->call<0>(c, t), this->call<1>(c, t), this->call<2>(c, t));
				return color;
			}
	};
}

#endif
