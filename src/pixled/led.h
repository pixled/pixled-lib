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

	class Led : public api::Led {
		private:
			Color _color;
		public:
			Color& color() override {
				return _color;
			}

			const Color& color() const override {
				return _color;
			}
	};

	class Strip : public api::Strip {
		private:
			uint16_t length;
			Led* leds;

		public:

			Strip(uint16_t length) : length(length) {
				leds = new Led[length];
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

			Led& operator[](uint16_t i) override {
				return leds[i];
			}

			void toArray(api::OutputFormat& format, uint8_t* output) override {
				for(uint16_t i = 0; i < length; i++) {
					const auto& color = leds[i].color();
					format.write(color, &output[3*i]);
				}
			}

			~Strip() {
				delete[] leds;
			}
	};
}
#endif
