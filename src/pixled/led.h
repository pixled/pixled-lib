#ifndef LED_H
#define LED_H

#include <iostream>
#include "api/led.h"

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
		uint8_t red() const override {return rgb.r;}
		uint8_t green() const override {return rgb.g;}
		uint8_t blue() const override {return rgb.b;}

		float hue() const override {return hsv.h;}
		float saturation() const override {return hsv.s;}
		float value() const override {return hsv.v;}

		void setRgb(uint8_t r, uint8_t g, uint8_t b) override;
		void setHsv(float, float, float) override;
	};

	template<typename color_t>
		class Led : public api::Led<color_t> {
			private:
				color_t _color;
			public:
				color_t& color() override {
					return color;
				}

				const color_t& color() const override {
					return color;
				}
		};

	template<typename led_t>
		class Strip : public api::Strip<led_t> {
			private:
				uint16_t length;
				led_t* leds;

			public:

				Strip(uint16_t length) : length(length) {
					leds = new led_t[length];
				}

				Strip(const Strip& other) = delete;
				Strip& operator=(const Strip&) = delete;
				Strip& operator=(Strip&&) = delete;

				void setLength(uint16_t length) override {
					this->length = length;
				}
				uint16_t getLength() const override {
					return length;
				}

				led_t& operator[](uint16_t i) override {
					return leds[i];
				}

				void toArray(uint8_t* output) override {
					for(uint16_t i = 0; i < length; i++) {
						const auto& color = leds[i].color();
						output[3*i+R] = color.red();
						output[3*i+G] = color.green();
						output[3*i+B] = color.blue();
					}
				}

				~Strip() {
					delete[] leds;
				}
		};
}
#endif
