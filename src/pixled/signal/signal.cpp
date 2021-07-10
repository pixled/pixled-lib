#include "signal.h"

namespace pixled { namespace signal {

	float Sine::operator()(point p, time t) const {
		return std::sin(2*PI * this->call<0>(p, t));
	}

	float Square::operator()(point p, time t) const {
		return std::sin(2*PI * this->call<0>(p, t)) > 0 ? 1 : -1;
	}

	float Triangle::operator()(point p, time t) const {
		return 2 / PI * std::asin(std::sin(
					2*PI * this->call<0>(p, t)
					));
	}

	float Sawtooth::operator()(point p, time t) const {
		return 2 / PI * std::atan(std::tan(
					2*PI * this->call<0>(p, t)
					));
	}
}}
