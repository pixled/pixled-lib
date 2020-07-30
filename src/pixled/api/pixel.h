#ifndef LED_API_H
#define LED_API_H
#include <cstdint>
#include <vector>
#include "geometry.h"

namespace pixled {
	namespace api {
		class Color {
			public:
				virtual uint8_t red() const = 0;
				virtual uint8_t green() const = 0;
				virtual uint8_t blue() const = 0;

				virtual float hue() const = 0;
				virtual float saturation() const = 0;
				virtual float brightness() const = 0;

				virtual void setRgb(uint8_t, uint8_t, uint8_t) = 0;
				virtual void setHsb(float, float, float) = 0;
		};

		class Pixel {
			public:
				virtual Color& color() = 0;
				virtual const Color& color() const = 0;
		};

		inline bool operator==(const Color& c1, const Color& c2) {
			return c1.red() == c2.red() && c1.green() == c2.green() && c1.blue() == c1.blue();
		}
	}
}
#endif
