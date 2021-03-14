#ifndef PIXLED_PIXEL_PIXEL_H
#define PIXLED_PIXEL_PIXEL_H

#include "../function.h"

namespace pixled { namespace chroma {
	class hsb : public Function<hsb, color, float, float, float> {
		public:
			using Function<hsb, color, float, float, float>::Function;

			color operator()(point c, time t) const override;
	};

	class rgb : public Function<rgb, color, uint8_t, uint8_t, uint8_t> {
		public:
			using Function<rgb, color, uint8_t, uint8_t, uint8_t>::Function;

			color operator()(point c, time t) const override;
	};
	static color RED {color::rgb(255, 0, 0)};
	static color GREEN {color::rgb(0, 255, 0)};
	static color BLUE {color::rgb(0, 0, 255)};
	static color LIGHT_RED {color::rgb(239, 71, 111)};
	static color YELLOW {color::rgb(255, 209, 102)};
	static color LIGHT_GREEN {color::rgb(6, 214, 160)};
	static color DARK_BLUE {color::rgb(17, 138, 178)};
	static color MIDNIGHT_BLUE {color::rgb(7, 59, 76)};
	static color PINK {color::rgb(255, 102, 255)};
	static color PURPLE {color::rgb(102, 0, 204)};
}}
#endif
