#ifndef PIXLED_FUNCTIONNAL_SIGNALS_H
#define PIXLED_FUNCTIONNAL_SIGNALS_H

#include "../function.h"

namespace pixled { namespace signal {
	/**
	 * Sine wave function.
	 *
	 * Since the specified parameter is a pixled \Function{float}, many type of
	 * waves can be defined.
	 *
	 * - Time dependent wave: `Sine(T() / period)`
	 * - Space dependent wave: `Sine(X() / lambda)`
	 * - Progressive wave: `Sine(X() / lambda - T() / period)`
	 *
	 * The spatial parameter X() might be replaced by Y(), or by any other
	 * coordinate dependent function. For example, to obtain a radial sine wave
	 * that originates from the point (8, 8):
	 * ```cpp
	 * Sine(
	 *     Distance(Point(X(), Y()), point(8, 8)) / lambda - T() / period
	 *     )
	 * ```
	 *
	 * See the `pixled/signal/sine.cpp` example below for concrete use cases of each
	 * wave type.
	 *
	 * Notice that, as usual, `lambda` and `period` might themselves by space
	 * and time dependent \Functions...
	 *
	 * @param float sin parameter
	 * @retval float returns sin(2*PI * this->call<0>(p, t))
	 */
	class Sine : public Function<Sine, float, float> {
		public:
			using Function<Sine, float, float>::Function;

			/*
			 * f1 : period
			 * f2 : param
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
