#include "led.h"

namespace base {
	void Color::setRgb(uint8_t r, uint8_t g, uint8_t b) {
		rgb.r = r;
		rgb.g = g;
		rgb.b = b;
	}

	void Color::setHsv(float h, float s, float v) {
		hsv.h = h;
		hsv.s = s;
		hsv.v = v;
	}
}
