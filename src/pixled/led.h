#ifndef LED_H
#define LED_H

#include <iostream>
#include "api/led.h"
#include "output.h"

namespace base {

	class Color : public api::Color {
		private:
			struct rgb_t {
				int r;
				int g;
				int b;
			};
			rgb_t rgb;

			struct hsv_t {
				float h;
				float s;
				float v;
			};
			hsv_t hsv;


		public:
		int red() override {return rgb.r;}
		int green() override {return rgb.g;}
		int blue() override {return rgb.b;}

		float hue() override {return hsv.h;}
		float saturation() override {return hsv.s;}
		float value() override {return hsv.v;}

		void setRgb(int r, int g, int b) override;
		void setHsv(float, float, float) override;
	};

	template<typename Color>
		class Led : public api::Led {
			private:
				Color _color;
			public:
				Color& color() override {
					return _color;
				}
		};

	template<int _length, typename led_t, typename rgb_array_t>
		class Strip : public api::Strip<_length, led_t, rgb_array_t> {
			private:
				led_t leds[_length];

			public:
				led_t& operator[](int i) override {
					return leds[i];
				}

				void toRgbArray(rgb_array_t& output) override {
					for(int i = 0; i < _length; i++) {
						api::Color& color = leds[i].color();
						rgb _rgb = rgb(color.red(), color.green(), color.blue());
						output[i] = _rgb;
					}
				}
		};
}
#endif
