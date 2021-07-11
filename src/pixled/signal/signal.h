#ifndef PIXLED_FUNCTIONNAL_SIGNALS_H
#define PIXLED_FUNCTIONNAL_SIGNALS_H

#include "../function.h"

namespace pixled { namespace signal {
	/**
	 * Sine wave function.
	 *
	 * Values returned are contained in `[-1, 1]`.
	 *
	 * ![Sine](sine.png) 
	 *
	 * `+` and `*` operators can be
	 * used to modulate the Sine wave as required.
	 * For example, to obtain values in `[0, 16]`:
	 * ```cpp
	 * 8.f * (1.f + Sine(...))
	 * ```
	 *
	 * More generally, to obtain values centered around a, with an amplitude of
	 * b, i.e. in `[a-b, a+b]`, so the total variation is `2*b`, use the
	 * following formula:
	 * ```cpp
	 * a + (b * Sine(...))
	 * ```
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
	 * @retval float `sin(2*PI * this->call<0>(p, t))`
	 */
	class Sine : public Function<Sine, float, float> {
		public:
			using Function<Sine, float, float>::Function;

			/*
			 * f1 : period
			 * f2 : param
			 */
			float operator()(led l, time t) const override;
	};

	/**
	 * Square wave function.
	 *
	 * Values returned are contained in `[-1, 1]`.
	 *
	 * ![Square](square.png) 
	 *
	 * `+` and `*` operators can be
	 * used to modulate the Square wave as required.
	 * For example, to obtain values in `[0, 16]`:
	 * ```cpp
	 * 8.f * (1.f + Square(...))
	 * ```
	 *
	 * More generally, to obtain values centered around a, with an amplitude of
	 * b, i.e. in `[a-b, a+b]`, so the total variation is `2*b`, use the
	 * following formula:
	 * ```cpp
	 * a + (b * Square(...))
	 * ```
	 *
	 * Differrent type of waves can be defined as for the Sine function.
	 *
	 * @param float square function parameter
	 * @retval float `sin(2*PI * this->call<0>(p, t)) > 0 ? 1 : -1`
	 */
	class Square : public Function<Square, float, float> {
		public:
			using Function<Square, float, float>::Function;

			float operator()(led l, time t) const override;
	};

	/**
	 * Triangle wave function.
	 *
	 * Values returned are contained in `[-1, 1]`.
	 *
	 * ![Triangle](triangle.png) 
	 *
	 * `+` and `*` operators can be
	 * used to modulate the Square wave as required.
	 * For example, to obtain values in `[0, 16]`:
	 * ```cpp
	 * 8.f * (1.f + Triangle(...))
	 * ```
	 *
	 * More generally, to obtain values centered around a, with an amplitude of
	 * b, i.e. in `[a-b, a+b]`, so the total variation is `2*b`, use the
	 * following formula:
	 * ```cpp
	 * a + (b * Triangle(...))
	 * ```
	 *
	 * Differrent type of waves can be defined as for the Sine function.
	 *
	 * @param float triangle function parameter
	 * @retval float `2/PI * asin(sin(2*PI * this->call<0>(p, t)))`
	 */
	class Triangle : public Function<Triangle, float, float> {
		public:
			using Function<Triangle, float, float>::Function;

			float operator()(led l, time t) const override;
	};

	/**
	 * Sawtooth wave function.
	 *
	 * Values returned are contained in `[-1, 1]`.
	 *
	 * ![Sawtooth](sawtooth.png) 
	 *
	 * `+` and `*` operators can be
	 * used to modulate the Square wave as required.
	 * For example, to obtain values in `[0, 16]`:
	 * ```cpp
	 * 8.f * (1.f + Sawtooth(...))
	 * ```
	 *
	 * More generally, to obtain values centered around a, with an amplitude of
	 * b, i.e. in `[a-b, a+b]`, so the total variation is `2*b`, use the
	 * following formula:
	 * ```cpp
	 * a + (b * Triangle(...))
	 * ```
	 *
	 * Differrent type of waves can be defined as for the Sine function.
	 *
	 * @param float triangle function parameter
	 * @retval float `2/PI * atan(tan(2*PI * this->call<0>(p, t)))`
	 */
	class Sawtooth : public Function<Sawtooth, float, float> {
		public:
			using Function<Sawtooth, float, float>::Function;

			float operator()(led l, time t) const override;
	};
}}
#endif
