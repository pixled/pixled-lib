#ifndef PIXLED_PIXEL_H
#define PIXLED_PIXEL_H

#include <iostream>

namespace pixled {
	class Color {
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

			Color& setRgb(uint8_t r, uint8_t g, uint8_t b);
			Color& setRed(uint8_t r);
			Color& setGreen(uint8_t r);
			Color& setBlue(uint8_t r);

			Color& setHsb(float, float, float);
			Color& setHue(float h);
			Color& setSaturation(float s);
			Color& setBrightness(float b);

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

	bool operator==(const Color& c1, const Color& c2);

	class Pixel {
		private:
			Color _color;
		public:
			Color& color()  {
				return _color;
			}

			const Color& color() const  {
				return _color;
			}
	};
}
#endif
