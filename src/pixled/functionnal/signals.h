#ifndef PIXLED_FUNCTIONNAL_SIGNALS_H
#define PIXLED_FUNCTIONNAL_SIGNALS_H

#include "../api/functionnal.h"

namespace pixled {
	class Sine : public api::TernaryFunction<float, float, float, float, Sine> {
		public:
			using api::TernaryFunction<float, float, float, float, Sine>::TernaryFunction;

			/*
			 * f1 : amplitude
			 * f2 : period
			 * f3 : x
			 */
			float operator()(api::Point p, Time t) const {
				return (*this->f1)(p, t) * std::sin(
						2*PIXLED_PI * (*this->f3)(p, t) / (*this->f2)(p, t));
			}
	};

	class Square : public api::TernaryFunction<float, float, float, float, Square> {
		public:
			using api::TernaryFunction<float, float, float, float, Square>::TernaryFunction;

			float operator()(api::Point p, Time t) const {
				if(std::sin(2*PIXLED_PI * (*this->f3)(p, t) / (*this->f2)(p, t)) > 0)
					return (*this->f1)(p, t);
				else
					return -(*this->f1)(p, t);
			}
	};

	class Triangle : public api::TernaryFunction<float, float, Time, Time, Triangle> {
		public:
			using api::TernaryFunction<float, float, Time, Time, Triangle>::TernaryFunction;

			float operator()(api::Point p, Time t) const {
				return 2 / PIXLED_PI * (*this->f1)(p, t) * std::asin(std::sin(
						(2*PIXLED_PI * (t - (*this->f3)(p, t))) / (*this->f2)(p, t)
						));
			}
	};

	class Sawtooth : public api::TernaryFunction<float, float, Time, Time, Sawtooth> {
		public:
			using api::TernaryFunction<float, float, Time, Time, Sawtooth>::TernaryFunction;

			float operator()(api::Point p, Time t) const {
				return 2 / PIXLED_PI * (*this->f1)(p, t) * std::atan(std::tan(
						(2*PIXLED_PI * (t - (*this->f3)(p, t))) / (*this->f2)(p, t)
						));
			}
	};
}
#endif
