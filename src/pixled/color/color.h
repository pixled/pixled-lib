#ifndef PIXLED_PIXEL_PIXEL_H
#define PIXLED_PIXEL_PIXEL_H

#include "../function.h"

namespace pixled { namespace color {
	class hsb : public Function<hsb, pixled::Color, float, float, float> {
		public:
			using Function<hsb, pixled::Color, float, float, float>::Function;

			pixled::Color operator()(Point c, Time t) const override;
	};

	class rgb : public Function<rgb, pixled::Color, uint8_t, uint8_t, uint8_t> {
		public:
			using Function<rgb, pixled::Color, uint8_t, uint8_t, uint8_t>::Function;

			pixled::Color operator()(Point c, Time t) const override;
	};
	static Color RED {Color::rgb(255, 0, 0)};
	static Color GREEN {Color::rgb(0, 255, 0)};
	static Color BLUE {Color::rgb(0, 0, 255)};
	static Color LIGHT_RED {Color::rgb(239, 71, 111)};
	static Color YELLOW {Color::rgb(255, 209, 102)};
	static Color LIGHT_GREEN {Color::rgb(6, 214, 160)};
	static Color DARK_BLUE {Color::rgb(17, 138, 178)};
	static Color MIDNIGHT_BLUE {Color::rgb(7, 59, 76)};
	static Color PINK {Color::rgb(255, 102, 255)};
	static Color PURPLE {Color::rgb(102, 0, 204)};
}}
#endif
