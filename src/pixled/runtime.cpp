#include "runtime.h"

namespace pixled {
	void Runtime::frame(Time t) {
		for(std::pair<Point, std::size_t> c : map) {
			output.write(animation(c.first, t), c.second);
		}
	}
	void Runtime::prev() {
		frame(_time--);
	}
	void Runtime::next() {
		frame(_time++);
	}
	Time Runtime::time() const {
		return _time;
	}
}
