#include "pixled/animation/animation.h"
#include "pixled/arithmetic/arithmetic.h"
#include "pixled/chroma/chroma.h"
#include "pixled/conditional/conditional.h"
#include "pixled/random/random.h"
#include "pixled/mapping/mapping.h"
#include "pixled/chrono/chrono.h"
#include "pixled/output.h"
#include "pixled/runtime.h"

/**
 * Main pixled namespace.
 */
namespace pixled {
	using namespace chroma;
	using namespace animation;
	using namespace arithmetic;
	using namespace conditional;
	using namespace geometry;
	using namespace mapping;
	using namespace random;
	using namespace signal;
	using namespace chrono;

	/**
	 * @example pixled/function/function.cpp
	 * 
	 * A pixled::Function example usage. A pixled::Function::call() helper
	 * function example usage is also presented.
	 */

	/**
	 * Namespace containing animation related functions.
	 */
	namespace animation {
		/**
		 * @example pixled/animation/rainbow.cpp
		 *
		 * A basic pixled::animation::Rainbow usage example.
		 *
		 * rainbow.gif | rainbow_dyn_b.gif
		 * ----------------|------------------
		 * ![Rainbow](rainbow.gif) | ![Dynamic Rainbow](rainbow_dyn_b.gif)
		 *
		 */

		/**
		 * @example pixled/animation/blink.cpp
		 *
		 * A pixled::animation::Blink usage example.
		 *
		 * blink_color.gif | blink_rainbow.gif
		 * ----------------|------------------
		 * ![Blink Color](blink_color.gif) | ![Blink Rainbow](blink_rainbow.gif)
		 *
		 */

		/**
		 * @example pixled/animation/blooming.cpp
		 *
		 * A pixled::animation::Blooming usage example.
		 *
		 * blooming_rainbow.gif | dynamic_blooming_rainbow.gif
		 * ----------------|------------------
		 * ![Blooming Rainbow](blooming_rainbow.gif) | ![Dynamic Blooming Rainbow](dynamic_blooming_rainbow.gif)
		 *
		 */

		/**
		 * @example pixled/animation/linear_unit_wave.cpp
		 *
		 * A pixled::animation::LinearUnitWave usage example.
		 *
		 * basic_linear_unit_wave.gif | rainbow_linear_unit_wave.gif
		 * ----------------------------|------------------------------
		 *  ![Basic Linear Unit Wave](basic_linear_unit_wave.gif) | ![Rainbow Linear
		 *  Unit Wave](rainbow_linear_unit_wave.gif)
		 *
		 */

		/**
		 * @example pixled/animation/radial_unit_wave.cpp
		 *
		 * A pixled::animation::RadialUnitWave usage example.
		 *
		 * basic_radial_unit_wave.gif | rainbow_radial_unit_wave.gif
		 * ----------------------------|------------------------------
		 *  ![Basic Radial Unit Wave](basic_radial_unit_wave.gif) | ![Rainbow Radial
		 *  Unit Wave](rainbow_radial_unit_wave.gif)
		 *
		 */

		/**
		 * @example pixled/animation/sequence.cpp
		 *
		 * A pixled::animation::Sequence usage example.
		 *
		 * sequence.gif ||
		 * -------------||
		 *  ![Sequence](sequence.gif) ||
		 *
		 */
	}

	/**
	 * Namespace containing arithmetic operators definitions adapted to
	 * \Functions.
	 *
	 * In order to use the defined operators with \Functions, it is **required**
	 * to import the pixled namespace with a `using namespace pixled`
	 * statement.
	 */
	namespace arithmetic {

	}

	/**
	 * Namesapce containing geometric functions.
	 */
	namespace geometry {
		/**
		 * @example pixled/geometry/index.cpp
		 *
		 * A led index based animation example.
		 *
		 * index.gif ||
		 * ----------||
		 *  ![Index](index.gif) ||
		 *
		 */
	}

	/**
	 * Namespace containing random generators and distributions.
	 */
	namespace random {
		/**
		 * @example pixled/random/uniform.cpp
		 *
		 * A pixled::random::UniformDistribution usage example.
		 *
		 * random_uniform_t.gif | random_uniform_xy_t.gif | random_uniform_xy_t_hue.gif
		 * --------------|------------------|----------------------
		 *  ![RandomT](random_uniform_t.gif) | ![RandomXYT](random_uniform_xy_t.gif) | ![RandoRandomXYT with hue](random_uniform_xy_t_hue.gif)
		 *
		 */

		/**
		 * @example pixled/random/normal.cpp
		 *
		 * A pixled::random::NormalDistribution usage example.
		 *
		 * random_normal_t.gif | random_normal_xy_t.gif | random_normal_xy_t_hue.gif
		 * --------------|------------------|----------------------
		 *  ![RandomT](random_normal_t.gif) | ![RandomXYT](random_normal_xy_t.gif) | ![RandoRandomXYT with hue](random_normal_xy_t_hue.gif)
		 *
		 */
	}

	/**
	 * Namespace containing comparison operators and the If statement.
	 */
	namespace conditional {
		/**
		 * @example pixled/conditional/conditional.cpp
		 *
		 * Demonstrates the If statement usage.
		 *
		 * conditional_eq.gif | conditional_less_greater.gif |
		 * -------------------||
		 * ![Conditionnal Equal](conditional_eq.gif) | ![Conditionnal Less
		 * Greater](conditional_less_greater.gif) |
		 *
		 */

	}

	/**
	 * Namespace containing wave functions.
	 */
	namespace signal {
		/**
		 * @example pixled/signal/sine.cpp
		 *
		 * Demonstrates the pixled::signal::Sine usage.
		 *
		 * sine_t.gif | sine_x.gif | sine_x_t.gif | sine_radial_t.gif
		 * -----------|------------|--------------|------------------
		 * ![Sine T](sine_t.gif) | ![Sine X](sine_x.gif) | ![Sine X T](sine_x_t.gif) | ![Sine Radial T](sine_radial_t.gif)
		 *
		 */

		/**
		 * @example pixled/signal/triangle.cpp
		 *
		 * A (relatively advanced) pixled::signal::Triangle example. But the
		 * Triangle function can be used exactly the same way as Sine, so also
		 * see the pixled/signal/sine.cpp example.
		 *
		 * insane_triangle_ratial_t.gif ||
		 * -----------------------------||
		 * ![Insane Triangle Ratial T](insane_triangle_radial_t.gif) ||
		 *
		 */

		/**
		 * @example pixled/signal/square.cpp
		 *
		 * Demonstrates the pixled::signal::Square usage.
		 *
		 * square_t.gif | square_x.gif | square_x_t.gif | square_radial_t.gif
		 * -----------|------------|--------------|------------------
		 * ![Square T](square_t.gif) | ![Square X](square_x.gif) | ![Square X T](square_x_t.gif) | ![Square Radial T](square_radial_t.gif)
		 *
		 */

		/**
		 * @example pixled/signal/sawtooth.cpp
		 *
		 * Demonstrates the pixled::signal::Sawtooth usage.
		 *
		 * sawtooth_t.gif | sawtooth_x.gif | sawtooth_x_t.gif | sawtooth_radial_t.gif
		 * -----------|------------|--------------|------------------
		 * ![Sawtooth T](sawtooth_t.gif) | ![Sawtooth X](sawtooth_x.gif) | ![Sawtooth X T](sawtooth_x_t.gif) | ![Sawtooth Radial T](sawtooth_radial_t.gif)
		 *
		 */
	}
}
