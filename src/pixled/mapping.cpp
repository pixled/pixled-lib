#include "mapping.h"

namespace pixled {
	void Mapping::push(const led& led) {
		b_box.stretchTo(led.location);
		_leds.push_back(led);
	}
}
