#ifndef PIXLED_PIXEL_PIXEL_H
#define PIXLED_PIXEL_PIXEL_H

#include "../function.h"

namespace pixled {
	/**
	 * Namespace containing color related functions and constants.
	 */
	namespace chroma {
		/**
		 * HSB color function.
		 *
		 * @note
		 * Notice the difference with pixled::color, that is a fundamental type
		 * used to store a color. pixled::chroma::hsb is a pixled::Function,
		 * what implies that hue, saturation and brightness can themselves be
		 * functions!
		 *
		 * @retval color color instance
		 * @param float hue in [0, 360]
		 * @param float saturation in [0, 1]
		 * @param float brightness in [0, 1]
		 */
		class hsb : public Function<hsb, color, float, float, float> {
			public:
				using Function<hsb, color, float, float, float>::Function;

				color operator()(point c, time t) const override;
		};

		/**
		 * RGB color function.
		 *
		 * @note
		 * Notice the difference with pixled::color, that is a fundamental type
		 * used to store a color. pixled::chroma::rgb is a pixled::Function,
		 * what implies that red, green and blue components can themselves be
		 * functions!
		 *
		 * @retval color color instance
		 * @param uint8_t red value in [0, 255]
		 * @param uint8_t green value in [0, 255]
		 * @param uint8_t blue value in [0, 255]
		 */
		class rgb : public Function<rgb, color, uint8_t, uint8_t, uint8_t> {
			public:
				using Function<rgb, color, uint8_t, uint8_t, uint8_t>::Function;

				color operator()(point c, time t) const override;
		};

		/**
		 * <div style="width:100%;height:1cm;background-color:rgb(255, 0, 0)"></div>
		 */
		static color RED {color::rgb(255, 0, 0)};
		/**
		 * <div style="width:100%;height:1cm;background-color:rgb(0, 255, 0)"></div>
		 */
		static color GREEN {color::rgb(0, 255, 0)};
		/**
		 * <div style="width:100%;height:1cm;background-color:rgb(0, 0, 255)"></div>
		 */
		static color BLUE {color::rgb(0, 0, 255)};
		/**
		 * <div style="width:100%;height:1cm;background-color:rgb(239, 71, 111)"></div>
		 */
		static color LIGHT_RED {color::rgb(239, 71, 111)};
		/**
		 * <div style="width:100%;height:1cm;background-color:rgb(255, 209, 102)"></div>
		 */
		static color YELLOW {color::rgb(255, 209, 102)};
		/**
		 * <div style="width:100%;height:1cm;background-color:rgb(6, 214, 160)"></div>
		 */
		static color LIGHT_GREEN {color::rgb(6, 214, 160)};
		/**
		 * <div style="width:100%;height:1cm;background-color:rgb(17, 138, 178)"></div>
		 */
		static color DARK_BLUE {color::rgb(17, 138, 178)};
		/**
		 * <div style="width:100%;height:1cm;background-color:rgb(7, 59, 76)"></div>
		 */
		static color MIDNIGHT_BLUE {color::rgb(7, 59, 76)};
		/**
		 * <div style="width:100%;height:1cm;background-color:rgb(255, 102, 255)"></div>
		 */
		static color PINK {color::rgb(255, 102, 255)};
		/**
		 * <div style="width:100%;height:1cm;background-color:rgb(102, 0, 204)"></div>
		 */
		static color PURPLE {color::rgb(102, 0, 204)};

	}
}
#endif
