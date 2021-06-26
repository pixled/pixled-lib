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
	using namespace arithmetic; using namespace conditional;
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
		 * uniform_t.gif | uniform_xy_t.gif | uniform_xy_t_hue.gif
		 * --------------|------------------|----------------------
		 *  ![RandomT](uniform_t.gif) | ![RandomXYT](uniform_xy_t.gif) | ![RandoRandomXYT with hue](uniform_xy_t_hue.gif)
		 *
		 */
	}
}
