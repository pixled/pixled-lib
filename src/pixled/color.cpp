#include "color.h"

namespace pixled {
	void color::hsb_to_rgb(const hsb_t& hsb, rgb_t& rgb) {
		double      hh, p, q, t, ff;
		long        i;
		double      r_out;
		double      g_out;
		double 	    b_out;

		float hue = hsb.h;
		float saturation = hsb.s;
		float brightness = hsb.b;

		if(saturation <= 0.0) {       // < is bogus, just shuts up warnings
			r_out = brightness;
			g_out = brightness;
			b_out = brightness;
			rgb.r = r_out * 255;
			rgb.g = g_out * 255;
			rgb.b = b_out * 255;
			return;
		}

		hh = hue;
		while(hh>= 360.0)
			hh -= 360.0;
		while(hh < 0)
			hh += 360.0;
		hh /= 60.0;
		i = (long)hh;
		ff = hh - i;
		p = brightness * (1.0 - saturation);
		q = brightness * (1.0 - (saturation * ff));
		t = brightness * (1.0 - (saturation * (1.0 - ff)));

		switch(i) {
			case 0:
				r_out = brightness;
				g_out = t;
				b_out = p;
				break;
			case 1:
				r_out = q;
				g_out = brightness;
				b_out = p;
				break;
			case 2:
				r_out = p;
				g_out = brightness;
				b_out = t;
				break;

			case 3:
				r_out = p;
				g_out = q;
				b_out = brightness;
				break;
			case 4:
				r_out = t;
				g_out = p;
				b_out = brightness;
				break;
			case 5:
			default:
				r_out = brightness;
				g_out = p;
				b_out = q;
				break;
		}

		rgb.r = r_out * 255;
		rgb.g = g_out * 255;
		rgb.b = b_out * 255;
	}

	void color::rgb_to_hsb(const rgb_t &rgb, hsb_t &hsb) {
		double      min, max, delta;

		min = rgb.r < rgb.g ? rgb.r : rgb.g;
		min = min  < rgb.b ? min  : rgb.b;

		max = rgb.r > rgb.g ? rgb.r : rgb.g;
		max = max  > rgb.b ? max  : rgb.b;

		hsb.b = max;                                // v
		delta = max - min;
		if (delta < 0.00001)
		{
			hsb.s = 0;
			hsb.h = 0; // undefined, maybe nan?
			return;
		}
		if( max > 0. ) { // NOTE: if Max is == 0, this divide would cause a crash
			hsb.s = (delta / max);                  // s
		} else {
			// if max is 0, then r = g = b = 0              
			// s = 0, h is undefined
			hsb.s = 0.;
			hsb.h = 0.;                            // its now undefined
			return;
		}
		if( rgb.r >= max )                           // > is bogus, just keeps compilor happy
			hsb.h = ( rgb.g - rgb.b ) / delta;        // between yellow & magenta
		else
			if( rgb.g >= max )
				hsb.h = 2. + ( rgb.b - rgb.r ) / delta;  // between cyan & yellow
			else
				hsb.h = 4. + ( rgb.r - rgb.g ) / delta;  // between magenta & cyan

		hsb.h *= 60.;                              // degrees

		if( hsb.h < 0. )
			hsb.h += 360.;
	}

	color& color::setRgb(uint8_t r, uint8_t g, uint8_t b) {
		_rgb.r = r;
		_rgb.g = g;
		_rgb.b = b;
		rgb_to_hsb(_rgb, _hsb);
		return *this;
	}

	color& color::setRed(uint8_t r) {
		_rgb.r = r;
		rgb_to_hsb(_rgb, _hsb);
		return *this;
	}

	color& color::setGreen(uint8_t g) {
		_rgb.g = g;
		rgb_to_hsb(_rgb, _hsb);
		return *this;
	}

	color& color::setBlue(uint8_t b) {
		_rgb.b = b;
		rgb_to_hsb(_rgb, _hsb);
		return *this;
	}

	color& color::setHsb(float h, float s, float b) {
		_hsb.h = h;
		_hsb.s = s;
		_hsb.b = b;
		hsb_to_rgb(_hsb, _rgb);
		return *this;
	}

	color& color::setHue(float h) {
		_hsb.h = h;
		hsb_to_rgb(_hsb, _rgb);
		return *this;
	}

	color& color::setSaturation(float s) {
		_hsb.s = s;
		hsb_to_rgb(_hsb, _rgb);
		return *this;
	}

	color& color::setBrightness(float b) {
		_hsb.b = b;
		hsb_to_rgb(_hsb, _rgb);
		return *this;
	}

	color color::rgb(uint8_t r, uint8_t g, uint8_t b) {
		color c;
		c.setRgb(r, g, b);
		return c;
	}

	color color::hsb(float h, float s, float v) {
		color c;
		c.setHsb(h, s, v);
		return c;
	}

	bool operator==(const color& c1, const color& c2) {
		return c1.red() == c2.red() && c1.green() == c2.green() && c1.blue() == c1.blue();
	}
}
