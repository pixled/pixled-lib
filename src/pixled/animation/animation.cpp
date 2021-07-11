#include "animation.h"

namespace pixled { namespace animation {

	float Rainbow::operator()(led l, time t) const {
		return 180.f * (sin(l, t) + 1.f);
	}

	float RainbowWave::operator()(led l, time t) const {
		float d = geometry::LineDistance(this->arg<2>(), l.location)(l, t);
		return 180.f * (1.f + std::sin(2*PI*(d / this->call<0>(l, t) - (float) t / this->call<1>(l, t))));
	}

	float RadialRainbowWave::operator()(led l, time t) const {
		float d = geometry::Distance(this->arg<2>(), l.location)(l, t);
		return 180.f * (1.f + std::sin(2*PI*(d / this->call<0>(l, t) - (float) t / this->call<1>(l, t))));
	}

	float LinearUnitWave::operator()(led l, time t) const {
		float d = geometry::LineDistance(this->arg<2>(), l.location)(l, t);
		return .5f * (1.f + std::sin(2*PI*(d / this->call<0>(l, t) - (float) t / this->call<1>(l, t))));
	}

	float RadialUnitWave::operator()(led l, time t) const {
		float d = geometry::Distance(this->arg<2>(), l.location)(l, t);
		return .5f * (1.f + std::sin(2*PI*(d / this->call<0>(l, t) - (float) t / this->call<1>(l, t))));
	}

	color Blooming::operator()(led l, time t) const {
		color color = this->call<0>(l, t);
		// Max distance from center point, where b = epsilon
		float D = this->call<2>(l, t);
		// Distance from c to center point
		float d = geometry::Distance(this->arg<1>(), l.location)(l, t);

		// The brightness decreases as a 1 / x light functions, scaled
		// so that when d = D, b = epsilon.
		float epsilon = 0.05;
		float alpha = (1 - epsilon) / (epsilon * D);
		float b = 1 / (1 + alpha * d);
		if(b < epsilon)
			b = 0.;

		color.setBrightness(b);
		return color;
	}

	color Sequence::operator()(led l, time t) const {
		if(t >= cache_time && t < cache_time + cache_time_duration)
			return (**cache)(l, t);
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
		return (*anim_ptr)(l, t);
	}

	Sequence* Sequence::copy() const {
		return new Sequence(*this);
	}

	color Blink::operator()(led l, time t) const {
		if(square(l, t) > 0) {
			return this->call<0>(l, t);
		}
		return black;
	}
}}
