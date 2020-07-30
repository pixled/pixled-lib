#include "animation.h"

namespace pixled {

	void Runtime::frame(Time t) {
		for(std::pair<api::Point, std::size_t> c : map) {
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

	float Rainbow::operator()(api::Point c, Time t) const {
		return 
			180.f * (std::sin(2*PIXLED_PI * t / (*this->f)(c, t)) + 1.f);
	}

	float RainbowWave::operator()(api::Point p, Time t) const {
		float d = LineDistance(*this->f2, p)(p, t);
		return 180.f * (1.f + std::sin(d / (*this->f1)(p, t) - (float) t / (*this->f3)(p, t)));
	}

	Color Blooming::operator()(api::Point c, Time t) const {
		Color color = (*this->f1)(c, t);
		// Max distance from center point, where b = epsilon
		float D = (*this->f3)(c, t);
		// Distance from c to center point
		float d = Distance(*this->f2, c)(c, t);

		// The brightness decreases as a 1 / x light functions, scaled
		// so that when d = D, b = epsilon.
		float epsilon = 0.05;
		float alpha = (1 - epsilon) / (epsilon * D);
		float b = 1 / (1 + alpha * d);
		if(b < epsilon)
			b = 0.;

		color.setHsb(
				color.hue(),
				color.saturation(),
				b);
		return color;
	}

	Color PixelView::operator()(api::Point c, Time t) const {
		if (c.x == (*f1)(c, t) && c.y == (*f2)(c, t))
			return (*f3)(c, t);
		return Color();
	}

	Sequence& Sequence::add(const api::Function<Color> &animation, Time duration) {
		animations.insert({this->duration, animation});
		cache_time = this->duration;
		cache = &animations.at(cache_time);
		this->duration+=duration;
		cache_time_duration=duration;
		return *this;
	}

	Color Sequence::operator()(api::Point p, Time t) const {
		if(t >= cache_time && t < cache_time + cache_time_duration)
			return (**cache)(p, t);
		auto it = animations.upper_bound(t % duration);
		auto prev_it = it;
		--prev_it;
		cache_time = t;
		if(it==animations.end()) {
			cache_time_duration = duration - prev_it->first;
		} else {
			cache_time_duration = it->first - prev_it->first;
		}
		auto& anim_ptr = prev_it->second;
		cache = &anim_ptr;
		return (*anim_ptr)(p, t);
	}

	Sequence* Sequence::copy() const {
		return new Sequence(*this);
	}

	Color Blink::operator()(api::Point p, Time t) const {
		if(square(p, t) > 0) {
			return (*this->f1)(p, t);
		}
		return black;
	}
}
