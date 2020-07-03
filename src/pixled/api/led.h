#ifndef LED_API_H
#define LED_API_H
#include <cstdint>
#include "output.h"

namespace pixled {
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


				//bool operator==(const Color& c1) const {
				//return c1.red() == this->red() && c1.green() == this->green() && c1.blue() == this->blue();
				//}
		};

		class Led {
			public:
				virtual Color& color() = 0;
				virtual const Color& color() const = 0;
		};

		class Strip {
			public:
				virtual uint16_t getLength() const = 0;
				virtual void setLength(uint16_t ) = 0;
				virtual Led& operator[](uint16_t i) = 0;

				virtual void toArray(OutputFormat& format, uint8_t* output) = 0;

		};

		inline bool operator==(const Color& c1, const Color& c2) {
			return c1.red() == c2.red() && c1.green() == c2.green() && c1.blue() == c1.blue();
		}
	}
}
#endif
