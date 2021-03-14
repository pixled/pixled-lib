#include "runtime.h"

namespace pixled {
	void Runtime::frame(time t) {
		for(std::pair<point, std::size_t> c : map) {
			output.write(animation(c.first, t), c.second);
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
