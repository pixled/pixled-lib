#ifndef PIXLED_PIXEL_H
#define PIXLED_PIXEL_H

#include <iostream>

namespace pixled {
	class color {
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
			uint8_t red() const {return _rgb.r;}
			uint8_t green() const {return _rgb.g;}
			uint8_t blue() const {return _rgb.b;}

			float hue() const {return _hsb.h;}
			float saturation() const {return _hsb.s;}
			float brightness() const {return _hsb.b;}

			color& setRgb(uint8_t r, uint8_t g, uint8_t b);
			color& setRed(uint8_t r);
			color& setGreen(uint8_t r);
			color& setBlue(uint8_t r);

			color& setHsb(float, float, float);
			color& setHue(float h);
			color& setSaturation(float s);
			color& setBrightness(float b);

			static color rgb(uint8_t r, uint8_t g, uint8_t b);
			static color hsb(float h, float s, float b);

			static color RED;
			static color GREEN;
			static color BLUE;
			static color LIGHT_RED;
			static color YELLOW;
			static color LIGHT_GREEN;
			static color DARK_BLUE;
			static color MIDNIGHT_BLUE;
			static color PINK;
			static color PURPLE;
	};

	bool operator==(const color& c1, const color& c2);
}
#endif
