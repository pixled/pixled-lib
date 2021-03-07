#include "signal.h"

namespace pixled { namespace signal {

	float Sine::operator()(Point p, Time t) const {
		return this->call<0>(p, t) * std::sin(2*PIXLED_PI * this->call<2>(p, t) / this->call<1>(p, t));
	}

	float Square::operator()(Point p, Time t) const {
		if(std::sin(2*PIXLED_PI * this->call<2>(p, t) / this->call<1>(p, t)) > 0)
			return this->call<0>(p, t);
		else
			return -this->call<0>(p, t);
	}

	float Triangle::operator()(Point p, Time t) const {
		return 2 / PIXLED_PI * this->call<0>(p, t) * std::asin(std::sin(
					(2*PIXLED_PI * this->call<2>(p, t)) / this->call<1>(p, t)
					));
	}

	float Sawtooth::operator()(Point p, Time t) const {
		return (2 / PIXLED_PI) * this->call<0>(p, t) * std::atan(std::tan(
					2*PIXLED_PI * this->call<2>(p, t) / (2 * this->call<1>(p, t))
					));
	}
}}
