#include "pixled.h"


/*
 * An example pixled::Function implementation, that return a pixled::point and
 * takes 3 arguments: pixled::point, pixled::time and a float.
 */
class F : public pixled::Function<F, pixled::point, pixled::point, pixled::time, float> {
	public:
		// Imports pixled::Function constructors
		using Function<F, pixled::point, pixled::point, pixled::time, float>::Function;

		/*
		 * F call operator, that implements pixled::base::Function<pixled::point>.
		 *
		 * Notice the difference between `p`, that is the point on which F is
		 * currently applied, and `this->call<0>(p, t)`, that is the point
		 * returned by the first **functionnal argument** passed to F, that
		 * returns a pixled::point.
		 *
		 * `this->call<i>(p, t)` calls the functionnal arguments of F,
		 * depending on the order specified in the `Args` list. Here, 0
		 * correspond to the first argument that returns a pixled::point, 1
		 * returns a pixled::time and 2 returns a `float`.
		 *
		 * Operations applied here are completely arbitrary.
		 */
		pixled::point operator()(pixled::led l, pixled::time t) const override {
			return pixled::point {
				this->call<0>(l, t).x * this->call<2>(l, t) + this->call<1>(l, t),
				this->call<0>(l, t).y
			};
		}
};

/*
 * Just wrap the construction of F in a function, to demonstrate that
 * `time_fct` can be safely destroyed when F is returned, without any memory
 * issues.
 */
F build_f() {
	// Required to use the * operator properly.
	// This directive can also be called at the namespace level.
	using namespace pixled;

	// A function that returns a pixled::time
	auto time_fct = 2 * pixled::chrono::T();

	return F(
			// A constant point, passed by r-value
			pixled::point(1, 1),
			// An function that returns a time, passed by l-value
			time_fct,
			// A function that returns a float, passed by r-value
			pixled::X()
			);
}
/*
 * A custom function example usage.
 *
 * @param Execution detail
 *
 * When F is applied to p=point(2, 0), t=10:
 * 1. time_fct(p, t), implicitly called by this->call<1>(p, t), returns 2*10=20
 * 2. X(p, t), implicitly called by this->call<2>(p, t), returns 2.
 * 3. The constant point is implicitly called by this->call<0>(p, t), and
 * always return {1, 1} so that `this->call<0>(p, t).x` = 1 and
 * `this->call<0>(p, t).y` = 1.
 *
 * Finally:
 * - F(p, t) = (1 * 2 + 20, 1) = (22, 1)
 */
int main(int argc, char** argv) {
	// Builds an f instance
	F f = build_f();

	// Apply F on p=point(2, 0) at t=10
	std::cout << f(pixled::led(pixled::point(2, 0), 4), 10) << std::endl;
}
