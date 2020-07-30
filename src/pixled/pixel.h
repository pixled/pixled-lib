#ifndef PIXLED_PIXEL_H
#define PIXLED_PIXEL_H

#include <iostream>
#include "api/pixel.h"

namespace pixled {

	class Color : public api::Color {
		private:
			struct rgb_t {
				int r;
				int g;
				int b;
			};
			rgb_t _rgb;

			struct hsb_t {
				float h;
				float s;
				float b;
			};
			hsb_t _hsb;


		public:
			static void rgb_to_hsb(const rgb_t& rgb, hsb_t& hsb);
			static void hsb_to_rgb(const hsb_t& hsb, rgb_t& rgb);
			uint8_t red() const override {return _rgb.r;}
			uint8_t green() const override {return _rgb.g;}
			uint8_t blue() const override {return _rgb.b;}

			float hue() const override {return _hsb.h;}
			float saturation() const override {return _hsb.s;}
			float brightness() const override {return _hsb.b;}

			void setRgb(uint8_t r, uint8_t g, uint8_t b) override;
			void setHsb(float, float, float) override;

			static Color rgb(uint8_t r, uint8_t g, uint8_t b);
	};

	class Pixel : public api::Pixel {
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
}
#endif
