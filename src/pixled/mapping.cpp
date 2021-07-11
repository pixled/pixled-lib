#include "mapping.h"

namespace pixled {

	bool operator==(const led& l1, const led& l2) {
			return (l1.index == l2.index) && (l1.location == l2.location);
	}

	bool led_equal::operator()(const led& l1, const led& l2) const {
		return l1 == l2;
	}

	void Mapping::push(const led& led) {
		b_box.stretchTo(led.location);
		_leds.push_back(led);
	}
}
