#ifndef PIXLED_FUNCTIONNAL_SIGNALS_H
#define PIXLED_FUNCTIONNAL_SIGNALS_H

#include "../function.h"

namespace pixled { namespace signal {
	class Sine : public Function<Sine, float, float, float, float> {
		public:
			using Function<Sine, float, float, float, float>::Function;

			/*
			 * f1 : amplitude
			 * f2 : period
			 * f3 : param
			 */
			float operator()(point p, time t) const override;
	};

	class Square : public Function<Square, float, float, float, float> {
		public:
			using Function<Square, float, float, float, float>::Function;

			float operator()(point p, time t) const override;
	};

	class Triangle : public Function<Triangle, float, float, time, time> {
		public:
			using Function<Triangle, float, float, time, time>::Function;

			float operator()(point p, time t) const override;
	};

	class Sawtooth : public Function<Sawtooth, float, float, float, float> {
		public:
			using Function<Sawtooth, float, float, float, float>::Function;

			float operator()(point p, time t) const override;
	};
}}
#endif
