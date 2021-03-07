#ifndef PIXLED_FUNCTIONNAL_SIGNALS_H
#define PIXLED_FUNCTIONNAL_SIGNALS_H

#include "../function.h"

namespace pixled { namespace signal {
	class Sine : public VarFunction<Sine, float, float, float, float> {
		public:
			using VarFunction<Sine, float, float, float, float>::VarFunction;

			/*
			 * f1 : amplitude
			 * f2 : period
			 * f3 : param
			 */
			float operator()(Point p, Time t) const override;
	};

	class Square : public VarFunction<Square, float, float, float, float> {
		public:
			using VarFunction<Square, float, float, float, float>::VarFunction;

			float operator()(Point p, Time t) const override;
	};

	class Triangle : public VarFunction<Triangle, float, float, Time, Time> {
		public:
			using VarFunction<Triangle, float, float, Time, Time>::VarFunction;

			float operator()(Point p, Time t) const override;
	};

	class Sawtooth : public VarFunction<Sawtooth, float, float, float, float> {
		public:
			using VarFunction<Sawtooth, float, float, float, float>::VarFunction;

			float operator()(Point p, Time t) const override;
	};
}}
#endif
