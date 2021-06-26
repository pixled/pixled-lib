#ifndef PIXLED_RUNTIME_H
#define PIXLED_RUNTIME_H

#include "output.h"
#include "function.h"
#include "mapping/mapping.h"

namespace pixled {
	/**
	 * Pixled Animation definition.
	 *
	 * An animation is simply defined as a base::Function that returns a color
	 * according to the current time and position in space.
	 */
	typedef base::Function<color> Animation;

	/**
	 * The purpose of the Runtime is to aggregate a Mapping and an Animation to
	 * perform the proper Output::write() operations.
	 *
	 * Since the Output interface is generic, the Runtime can be used on any
	 * device.
	 *
	 * However, there is no notion of `fps` in this class, since this concept
	 * is highly dependent on the device (and so on the Output) on which
	 * pixled is used.
	 */
	class Runtime {
		private:
			unsigned long _time = 0;
			Mapping& mapping;
			Output& output;
			Animation& animation;

			/**
			 * Builds the frame correspondind to `animation` at time `t` and
			 * write each color to each led defined by `mapping` using
			 * `output`.
			 */
			void frame(time t);


		public:
			/**
			 * Runtime constructor.
			 *
			 * @param mapping led mapping: specifies the leds currently in the
			 * system
			 * @param output led output: writes animation colors to each led
			 * @param animation animation to run
			 */
			Runtime(Mapping& mapping, Output& output, Animation& animation)
				: mapping(mapping), output(output), animation(animation) {}

			/**
			 * Steps the Runtime backward, builds the correspondind frame using
			 * the provided `animation`, and writes each color to leds defined
			 * in `mapping` using the `output`.
			 */
			void prev();
			/**
			 * Steps the Runtime forward, builds the correspondind frame using
			 * the provided `animation`, and writes each color to leds defined
			 * in `mapping` using the `output`.
			 */
			void next();

			/**
			 * Returns the current time step of the Runtime.
			 *
			 * @return current time
			 */
			time current_time() const;
	};
}
#endif
