#ifndef LED_API_H
#define LED_API_H
#include <cstdint>
#include "output.h"

namespace api {
	class Color {
		public:
			virtual uint8_t red() const = 0;
			virtual uint8_t green() const = 0;
			virtual uint8_t blue() const = 0;

			virtual float hue() const = 0;
			virtual float saturation() const = 0;
			virtual float value() const = 0;

			virtual void setRgb(uint8_t, uint8_t, uint8_t) = 0;
			virtual void setHsv(float, float, float) = 0;
	};

	template<typename color_t>
	class Led {
		public:
			virtual color_t& color() = 0;
			virtual const color_t& color() const = 0;
	};

	template<typename led_t>
		class Strip {
			public:
				virtual uint16_t getLength() const = 0;
				virtual void setLength(uint16_t ) = 0;
				virtual led_t& operator[](uint16_t i) = 0;

				virtual void toArray(uint8_t* output) = 0;

		};
}
#endif
