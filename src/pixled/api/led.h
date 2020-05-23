#ifndef LED_API_H
#define LED_API_H
#include "output.h"

namespace api {
	class Color {
		public:
			virtual int red() = 0;
			virtual int green() = 0;
			virtual int blue() = 0;

			virtual float hue() = 0;
			virtual float saturation() = 0;
			virtual float value() = 0;

			virtual void setRgb(int, int, int) = 0;
			virtual void setHsv(float, float, float) = 0;
	};

	class Led {
		public:
			virtual Color& color() = 0;


	};
	template<int _length, typename led_t, typename rgb_array_t>
		class Strip {
			public:
				static constexpr int length() {return _length;}
				static_assert(
					Strip::length() == rgb_array_t::length(),
					"The specified rgb_array_t length does not correspond to Strip length.");
			public:
				virtual led_t& operator[](int i) = 0;

				virtual void toRgbArray(rgb_array_t& output) = 0;

		};
}
#endif
