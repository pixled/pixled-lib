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

			Color& setRgb(uint8_t r, uint8_t g, uint8_t b) override;
			Color& setRed(uint8_t r) override;
			Color& setGreen(uint8_t r) override;
			Color& setBlue(uint8_t r) override;

			Color& setHsb(float, float, float) override;
			Color& setHue(float h) override;
			Color& setSaturation(float s) override;
			Color& setBrightness(float b) override;

			static Color rgb(uint8_t r, uint8_t g, uint8_t b);
			static Color hsb(float h, float s, float b);

			static Color RED();
			static Color GREEN();
			static Color BLUE();
			static Color LIGHT_RED();
			static Color YELLOW();
			static Color LIGHT_GREEN();
			static Color DARK_BLUE();
			static Color MIDNIGHT_BLUE();
			static Color PINK();
			static Color PURPLE();
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
