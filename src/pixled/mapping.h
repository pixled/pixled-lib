#ifndef PIXLED_MAPPING_API_H
#define PIXLED_MAPPING_API_H

#include <vector>
#include "geometry.h"

namespace pixled {
	/**
	 * Type used to index leds on a led strip.
	 */
	typedef std::size_t index_t;

	/**
	 * Basic structure used to represent an led.
	 *
	 * A 2D `location` is associated to the led with the specified `index` on
	 * the led strip.
	 */
	struct led {
		/**
		 * Led location.
		 */
		point location;
		/**
		 * Led index on the led strip.
		 */
		index_t index;

		/**
		 * led constructor.
		 *
		 * @param location led location
		 * @param index led index on the led strip
		 */
		led(point location, index_t index)
			: location(location), index(index) {}
	};

	/**
	 * The Mapping is an essential pixled component.
	 *
	 * It is used to described all the leds contained in the current system, so
	 * that the Runtime can apply an Animation on each led.
	 *
	 * A Mapping can be used to define **any** 2D led shape, without any
	 * restriction.
	 *
	 * See the \ref mapping namespace for predefined mappings.
	 */
	struct Mapping {
		private:
			std::vector<led> _leds;
			bounding_box b_box;
		public:
			/**
			 * Returns all the leds contained in this mapping.
			 */
			const std::vector<led>& leds() const {
				return _leds;
			}

			/**
			 * Push a new led in the mapping. It is the responsability of the
			 * user to ensure that the led indexes are consistent.
			 *
			 * @param led led to add to the mapping
			 */
			void push(const led& led);

			/**
			 * Minimalist box around all the leds currently contained in the
			 * mapping.
			 * 
			 * The bounding box is updated each time push() is called.
			 *
			 * @return mapping bounding box
			 */
			box boundingBox() const {return b_box;};
	};
}
#endif
