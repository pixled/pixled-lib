#include "runtime.h"

namespace pixled {
	void Runtime::frame(time t) {
		for(auto led : mapping.leds()) {
			output.write(animation(led, t), led.index);
		}
	}
	void Runtime::prev() {
		frame(_time--);
	}
	void Runtime::next() {
		frame(_time++);
	}
	time Runtime::current_time() const {
		return _time;
	}
}
