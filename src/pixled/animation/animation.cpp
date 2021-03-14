#include "animation.h"

namespace pixled { namespace animation {
	float SinT::operator()(point c, time t) const {
		return 0.5f * (std::sin(2*PIXLED_PI * t / this->call<0>(c, t)) + 1.f);
	}

	float Rainbow::operator()(point c, time t) const {
		return 360.f * sin(c, t);
			//180.f * (std::sin(2*PIXLED_PI * t / this->call<0>(c, t)) + 1.f);
	}

	float RainbowWave::operator()(point p, time t) const {
		float d = geometry::LineDistance(this->arg<1>(), p)(p, t);
		return 180.f * (1.f + std::sin(2*PIXLED_PI*(d / this->call<0>(p, t) - (float) t / this->call<2>(p, t))));
	}

	float RadialRainbowWave::operator()(point p, time t) const {
		float d = geometry::Distance(this->arg<1>(), p)(p, t);
		return 180.f * (1.f + std::sin(2*PIXLED_PI*(d / this->call<0>(p, t) - (float) t / this->call<2>(p, t))));
	}

	float SpatialUnitWave::operator()(point p, time t) const {
		float d = geometry::LineDistance(this->arg<1>(), p)(p, t);
		return .5f * (1.f + std::sin(2*PIXLED_PI*(d / this->call<0>(p, t) - (float) t / this->call<2>(p, t))));
	}

	color Blooming::operator()(point c, time t) const {
		color color = this->call<0>(c, t);
		// Max distance from center point, where b = epsilon
		float D = this->call<2>(c, t);
		// Distance from c to center point
		float d = geometry::Distance(this->arg<1>(), c)(c, t);

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

	color PixelView::operator()(point c, time t) const {
		if (c.x == this->call<0>(c, t) && c.y == this->call<1>(c, t))
			return this->call<2>(c, t);
		return color();
	}

	color Sequence::operator()(point p, time t) const {
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

	color Blink::operator()(point p, time t) const {
		if(square(p, t) > 0) {
			return this->call<0>(p, t);
		}
		return black;
	}
}}
