#ifndef OUTPUT_API_H
#define OUTPUT_API_H

#include "color.h"
#include <cstdint>

namespace pixled {
	/**
	 * Generic Output interface.
	 *
	 * The purpose of the output is to write each color to each led of a led
	 * strip.
	 *
	 * Implementations are completely free about how to handle the write
	 * operation: the output might be a gif, a generic buffer, a direct output
	 * to a real led strip on embedded systems, a bridge to a third party led
	 * driver library...
	 *
	 * The write() method is automatically called by the Runtime, according to
	 * the current mapping and animation.
	 */
	class Output {
		public:
			/**
			 * Writes the `color` to the led at index `i` in the led strip.
			 *
			 * @param color led color
			 * @param i led index
			 */
			virtual void write(const color& color, std::size_t i) = 0;

	};
}
#endif
