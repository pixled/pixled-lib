#ifndef PIXLED_FUNCTIONNAL_SIGNALS_H
#define PIXLED_FUNCTIONNAL_SIGNALS_H

#include "../api/functionnal.h"

namespace pixled {
	class Sine : public VarFunction<Sine, float, float, float, float> {
		public:
			using VarFunction<Sine, float, float, float, float>::VarFunction;

			/*
			 * f1 : amplitude
			 * f2 : period
			 * f3 : param
			 */
			float operator()(Point p, Time t) const {
				return this->call<0>(p, t) * std::sin(2*PIXLED_PI * this->call<2>(p, t) / this->call<1>(p, t));
			}
	};

	class Square : public VarFunction<Square, float, float, float, float> {
		public:
			using VarFunction<Square, float, float, float, float>::VarFunction;

			float operator()(Point p, Time t) const {
				if(std::sin(2*PIXLED_PI * this->call<2>(p, t) / this->call<1>(p, t)) > 0)
					return this->call<0>(p, t);
				else
					return -this->call<0>(p, t);
			}
	};

	class Triangle : public VarFunction<Triangle, float, float, Time, Time> {
		public:
			using VarFunction<Triangle, float, float, Time, Time>::VarFunction;

			float operator()(Point p, Time t) const {
				return 2 / PIXLED_PI * this->call<0>(p, t) * std::asin(std::sin(
						(2*PIXLED_PI * this->call<2>(p, t)) / this->call<1>(p, t)
						));
			}
	};

	class Sawtooth : public VarFunction<Sawtooth, float, float, float, float> {
		public:
			using VarFunction<Sawtooth, float, float, float, float>::VarFunction;

			float operator()(Point p, Time t) const {
				return (2 / PIXLED_PI) * this->call<0>(p, t) * std::atan(std::tan(
						2*PIXLED_PI * this->call<2>(p, t) / (2 * this->call<1>(p, t))
						));
			}
	};
}
#endif
