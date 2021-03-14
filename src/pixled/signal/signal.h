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
			float operator()(Point p, Time t) const override;
	};

	class Square : public Function<Square, float, float, float, float> {
		public:
			using Function<Square, float, float, float, float>::Function;

			float operator()(Point p, Time t) const override;
	};

	class Triangle : public Function<Triangle, float, float, Time, Time> {
		public:
			using Function<Triangle, float, float, Time, Time>::Function;

			float operator()(Point p, Time t) const override;
	};

	class Sawtooth : public Function<Sawtooth, float, float, float, float> {
		public:
			using Function<Sawtooth, float, float, float, float>::Function;

			float operator()(Point p, Time t) const override;
	};
}}
#endif
