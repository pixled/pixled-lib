#ifndef PIXLED_PIXEL_H
#define PIXLED_PIXEL_H

#include <iostream>

namespace pixled {
	/**
	 * Fundamental type representing a color.
	 */
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

			static void rgb_to_hsb(const rgb_t& rgb, hsb_t& hsb);
			static void hsb_to_rgb(const hsb_t& hsb, rgb_t& rgb);

		public:
			/**
			 * Red color component, in [0, 255].
			 */
			uint8_t red() const {return _rgb.r;}
			/**
			 * Green color component, in [0, 255].
			 */
			uint8_t green() const {return _rgb.g;}
			/**
			 * Blue color component, in [0, 255].
			 */
			uint8_t blue() const {return _rgb.b;}

			/**
			 * Hue, in [0, 360].
			 */
			float hue() const {return _hsb.h;}
			/**
			 * Saturation, in [0, 1].
			 */
			float saturation() const {return _hsb.s;}
			/**
			 * Brightness, in [0, 1].
			 */
			float brightness() const {return _hsb.b;}

			/**
			 * Sets the RGB values of this color.
			 *
			 * @param r red
			 * @param g green
			 * @param b blue
			 */
			color& setRgb(uint8_t r, uint8_t g, uint8_t b);
			/**
			 * Sets the Red component value of this color.
			 *
			 * @param r red
			 */
			color& setRed(uint8_t r);
			/**
			 * Sets the Green component value of this color.
			 *
			 * @param g green
			 */
			color& setGreen(uint8_t g);
			/**
			 * Sets the Blue component value of this color.
			 *
			 * @param b blue
			 */
			color& setBlue(uint8_t b);

			/**
			 * Sets the HSB values of this color.
			 *
			 * @param h hue
			 * @param s saturation
			 * @param b brightness
			 */
			color& setHsb(float h, float s, float b);
			/**
			 * Sets the hue of this color.
			 *
			 * @param h hue
			 */
			color& setHue(float h);
			/**
			 * Sets the saturation of this color.
			 *
			 * @param s saturation.
			 */
			color& setSaturation(float s);
			/**
			 * Sets the brightness of this color.
			 *
			 * @param b brightness.
			 */
			color& setBrightness(float b);

			/**
			 * Builds a color instance from RGB values.
			 *
			 * @param r red
			 * @param g green
			 * @param b blue
			 * @return color instance
			 */
			static color rgb(uint8_t r, uint8_t g, uint8_t b);
			/**
			 * Builds a color instance from HSB values.
			 *
			 * @param h hue
			 * @param s saturation
			 * @param b brightness
			 * @return color instance
			 */
			static color hsb(float h, float s, float b);
	};

	/**
	 * Checks if the two colors are equal, i.e. if their red / green / blue
	 * components are equal.
	 *
	 * @return true iff `c1` == `c2`
	 */
	bool operator==(const color& c1, const color& c2);
}
#endif
