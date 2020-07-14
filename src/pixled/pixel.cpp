#include "pixel.h"

namespace pixled {
	void Color::hsb_to_rgb(const hsv_t& hsv, rgb_t& rgb) {
		double      hh, p, q, t, ff;
		long        i;
		double      r_out;
		double      g_out;
		double 	    b_out;

		float hue = hsv.h;
		float saturation = hsv.s;
		float brightness = hsv.v;

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
		if(hh >= 360.0) hh = 0.0;
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

	void Color::rgb_to_hsb(const rgb_t &rgb, hsv_t &hsb) {
		double      min, max, delta;

		min = rgb.r < rgb.g ? rgb.r : rgb.g;
		min = min  < rgb.b ? min  : rgb.b;

		max = rgb.r > rgb.g ? rgb.r : rgb.g;
		max = max  > rgb.b ? max  : rgb.b;

		hsb.v = max;                                // v
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

	void Color::setRgb(uint8_t r, uint8_t g, uint8_t b) {
		rgb.r = r;
		rgb.g = g;
		rgb.b = b;
		rgb_to_hsb(rgb, hsv);
	}

	void Color::setHsv(float h, float s, float v) {
		hsv.h = h;
		hsv.s = s;
		hsv.v = v;
		hsb_to_rgb(hsv, rgb);
	}

	StripMapping::StripMapping(std::size_t length) {
		for(std::size_t i = 0; i < length; i++) {
			coordinates.push_back(api::Point(i, 0));
		}
	}

	std::size_t StripMapping::map(api::Point c) const {
		return c.x;
	}

	typename StripMapping::coordinates_iterator StripMapping::begin() const {
		return coordinates.begin();
	}

	typename StripMapping::coordinates_iterator StripMapping::end() const {
		return coordinates.end();
	}
}
